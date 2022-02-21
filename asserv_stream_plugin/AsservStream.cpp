#include "AsservStream.h"
#include <QFile>
#include <QMessageBox>
#include <thread>
#include <mutex>
#include <chrono>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions      */
#include <cstdint>
#include <QInputDialog>
#include <QStringList>
#include <QDir>
#include <QMessageBox>
#include <cmath>
#include "ui_asservstreamcontrolpanel.h"
#include "AsservStreamControlPanel.h"
#include <libconfig.h++>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <QMetaClassInfo>



#define ASSERV_FREQ 300.0
#define BAUDRATE    QSerialPort::Baud115200
using namespace std;
using namespace libconfig;
using namespace PJ;


AsservStream::AsservStream():_running(false),fd(-1), fdLog(-1), deviceOpened(false), nbValuesInSample(0)
{
    controlPanelWindows = nullptr;
}

bool AsservStream::readConfigFile()
{
	string dir_path("");
	for(int i=0; i<this->metaObject()->classInfoCount(); i++)
	{
		QMetaClassInfo info = this->metaObject()->classInfo(i);
		string searched_str("so_file_dir");
		string curr_name(info.name());
		if(searched_str == curr_name)
		{
			dir_path = string(info.value());
			break;
		}
	}

	libconfig::Config cfg;

	string full_path = dir_path + string("/network_struct.cfg");
	try
	{
		cfg.readFile(full_path.c_str());
	}
	catch(const FileIOException &fioex)
	{
		std::cerr << "I/O error while reading file :" << full_path << std::endl;
		return false;
	}

	try
	{
		const libconfig::Setting &root = cfg.getRoot();
		const libconfig::Setting &network_struct = root.lookup("network_struct");

		asservStream_fields.push_back("timestamp");
		for (int n = 0; n < network_struct.getLength(); ++n)
		{
			asservStream_fields.push_back(network_struct[n]);
		}
	}
	catch (...)
	{
		std::cerr << "Error while parsing file :" << full_path << std::endl;
		return false;
	}

	std::lock_guard<std::mutex> lock( mutex() );
	for (int n = 0; n < asservStream_fields.size(); ++n)
	{
		dataMap().addNumeric(asservStream_fields[n]);
		printf("[%d] => %s \n", n, asservStream_fields[n].c_str());
	}

	nbValuesInSample = asservStream_fields.size();
	uartDecoder.setNumberValuesInSample(nbValuesInSample);

	return true;
}

bool AsservStream::openPort()
{
    bool ok;

    QDir devDir("/dev/");
    QStringList ttyListAbsolutePath;

    QFileInfoList list = devDir.entryInfoList(QStringList() << "ttyACM*", QDir::System);
    for (int i = list.size() - 1; i >= 0; i--)
        ttyListAbsolutePath << list.at(i).absoluteFilePath();

    QString portName = QInputDialog::getItem(nullptr, tr("Which tty use ?"), tr("/dev/tty?"), ttyListAbsolutePath, 0, false, &ok);

    if (!ok)
        return false;
    device = new QSerialPort(this);
    device->setPortName(portName);
    deviceOpened = device->open(QIODevice::ReadWrite);

    if(deviceOpened){
        device->setBaudRate(BAUDRATE);
        device->setDataBits(QSerialPort::Data8);
        device->setParity(QSerialPort::NoParity);
        device->setStopBits(QSerialPort::OneStop);
        device->setFlowControl(QSerialPort::NoFlowControl);
        device->flush();
        printf("opened port %s\n", portName.toStdString().c_str());
        return true;

    } else{
        printf("Unable to open %s\n", portName.toStdString().c_str());
        return false;
    }

}

bool AsservStream::start(QStringList*)
{
	if( !readConfigFile() )
			return false;

    bool ok = openPort();
    bool tryAgain = !ok;
    while (tryAgain)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Unable to open port", "Unable to open port\nTry again?",
                QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
        {
            tryAgain = false;
        }
        else
        {
            ok = openPort();
            tryAgain = !ok;
        }
    }

    if (ok)
    {
        std::lock_guard < std::mutex > lock(mutex());
        // Insert dummy Point. it seems that there's a regression on plotjuggler, this dirty hack seems now necessary
        for (auto &it : dataMap().numeric)
        {
            auto &plot = it.second;
            plot.pushBack(PlotData::Point(0, 0));
        }
        _running = true;
        _thread = std::thread([this]()
        {   this->loop();});

        controlPanelWindows = new AsservStreamControlPanel(new Ui_AsservStreamControlPanel, &uartDecoder, fd, fdLog);
        controlPanelWindows->show();

        return true;
    }
    else
    {
        return false;
    }
}

void AsservStream::shutdown()
{
    _running = false;
    if( _thread.joinable()) _thread.join();

    if(controlPanelWindows != nullptr)
    	controlPanelWindows->close();

    device->clearError();
    device->close();
    delete device;


}

bool AsservStream::isRunning() const { return _running; }

AsservStream::~AsservStream()
{
    shutdown();
    if(controlPanelWindows != nullptr)
    	delete(controlPanelWindows);

    emit closed();
}

void AsservStream::pushSingleCycle()
{
	std::vector<float> sample;
	bool added_data = false;
    while (uartDecoder.getDecodedSample(sample))
    {
    	double timestamp = double(sample[0]) * 1.0 / ASSERV_FREQ; // 1st value in sample is the timestamp
        std::lock_guard < std::mutex > lock(mutex());
        for (auto &it : dataMap().numeric)
        {
            double value = getValueFromName(it.first, sample);

            if (std::isnan(value))
                value = 0;

            auto &plot = it.second;
            plot.pushBack(PlotData::Point(timestamp, value));
        }
        added_data = true;
    }
    if(added_data)
    	emit dataReceived();
}

void AsservStream::loop()
{
    _running = true;
    while (_running && deviceOpened)
    {
        uint8_t read_buffer[nbValuesInSample*4 + 4];
        int bytes_read = 0;

        while (device->bytesAvailable() < (nbValuesInSample*4 + 4)){
            device->waitForReadyRead(1000);
        }

        bytes_read = device->read((char*)read_buffer, nbValuesInSample*4 + 4);

        if (bytes_read > 0)
            uartDecoder.processBytes(read_buffer, bytes_read);

        pushSingleCycle();
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }

}

double AsservStream::getValueFromName(const std::string &name, std::vector<float> &sample)
{
	for (int n = 0; n < asservStream_fields.size(); ++n)
	{
		if ( name == asservStream_fields[n])
			return sample[n];
	}
	return 0;

}



bool AsservStream::xmlSaveState(QDomDocument &doc, QDomElement &parent_element) const 
{
    return true;
}
    
bool AsservStream::xmlLoadState(const QDomElement &parent_element)
{
    return false;
}
