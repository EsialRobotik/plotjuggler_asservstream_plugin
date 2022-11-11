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


#define ASSERV_FREQ 600.0
using namespace std;
using namespace libconfig;
using namespace PJ;

AsservStream::AsservStream():_running(false), fdLog(-1), fd(-1), deviceOpened(false)
{
    controlPanelWindows = nullptr;
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

    fd = open(portName.toStdString().c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
     {
         printf("Unable to open %s\n", portName.toStdString().c_str());
         return false;
     }
     else
     {
         printf("Port %s opened\n", portName.toStdString().c_str());

         struct termios termios_p;
         tcgetattr(fd, &termios_p);
         termios_p.c_cflag = B115200;
         termios_p.c_cflag |= CS8;
         termios_p.c_cflag |= CREAD;
         termios_p.c_iflag = IGNPAR | IGNBRK;
         termios_p.c_cflag |= CLOCAL;
         termios_p.c_oflag = 0;
         termios_p.c_lflag = 0;
         termios_p.c_cc[VTIME] = 0;
         termios_p.c_cc[VMIN] = 1;
         tcsetattr(fd, TCSANOW, &termios_p);
         tcflush(fd, TCOFLUSH);
         tcflush(fd, TCIFLUSH);
         fdLog = open("commandLog" , O_WRONLY | O_APPEND | O_CREAT, S_IRUSR |S_IWUSR | S_IRGRP|S_IWGRP );
         return true;
     }
}

bool AsservStream::start(QStringList*)
{
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
        const uint32_t synchroWord_connection = 0xDEADBEEF;
        int dummy = write(fd, (char*)&synchroWord_connection, sizeof(synchroWord_connection));

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

        controlPanelWindows = new AsservStreamControlPanel(new Ui_AsservStreamControlPanel, &uartDecoder, nullptr, fdLog);
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
	if( _running )
	{
		_running = false;
		if( _thread.joinable()) _thread.join();

		if(controlPanelWindows != nullptr)
			controlPanelWindows->close();

		if(fd != -1)
		    close(fd);
	}

}

bool AsservStream::isRunning() const { return _running; }

AsservStream::~AsservStream()
{
    shutdown();
    if(controlPanelWindows != nullptr)
    	delete(controlPanelWindows);
}

void AsservStream::pushSingleCycle()
{
    if( uartDecoder.getNewDescription( asservStream_fields))
    {
        std::lock_guard<std::mutex> lock( mutex() );
        for (int n = 0; n < asservStream_fields.size(); ++n)
        {
            dataMap().addNumeric(asservStream_fields[n]);
            printf("[%d] => %s \n", n, asservStream_fields[n].c_str());
        }
    }
    else
    {
        std::vector<float> sample;
        bool added_data = false;
        while (uartDecoder.getDecodedSample(sample))
        {
            double timestamp = double(getValueFromName("timestamp", sample)) * (1.0/ASSERV_FREQ); // 1st value in sample is the timestamp
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
            emit this->dataReceived();
    }
}

void AsservStream::loop()
{
    _running = true;
    while (_running && fd != -1)
    {
        uint8_t read_buffer[512];
        int bytes_read = read(fd, read_buffer, sizeof(read_buffer));


        if (bytes_read > 0)
        {
            uartDecoder.processBytes(read_buffer, bytes_read);
        }

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

