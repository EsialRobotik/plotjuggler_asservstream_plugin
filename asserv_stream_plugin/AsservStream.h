#ifndef ASSERVSTREAM_H
#define ASSERVSTREAM_H

#include <QMetaObject>
#include <QtPlugin>
#include <thread>
#include "PlotJuggler/datastreamer_base.h"
#include <map>
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include <cstring>
#include <fstream>
#include <vector>
#include "AsservStream_uartDecoder.h"

class AsservStreamControlPanel;

class  AsservStream: public PJ::DataStreamer
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cheff.PlotJuggler3.AsservStream")
    Q_INTERFACES(PJ::DataStreamer)
    Q_CLASSINFO("so_file_dir", PLUGIN_BUIL_DIR)

public:

    AsservStream();

    virtual bool start(QStringList*) override;

    virtual void shutdown() override;

    virtual bool isRunning() const override;

    virtual ~AsservStream();

    virtual const char* name() const override { return PLUGIN_NAME; }

    virtual bool isDebugPlugin() override { return false; }

    virtual bool xmlSaveState(QDomDocument &doc, QDomElement &parent_element) const override;

    virtual bool xmlLoadState(const QDomElement &parent_element ) override;

private:

     void loop();
     bool readConfigFile();
     bool openPort();
     void pushSingleCycle();
     double getValueFromName(const std::string &name, std::vector<float> &sample);

     std::thread _thread;
     bool _running;
     int fd;
     int fdLog;
     AsservStream_uartDecoder uartDecoder;
     AsservStreamControlPanel *controlPanelWindows;
     QSerialPort * device;
     std::vector<std::string> asservStream_fields;
     bool deviceOpened;
     int nbValuesInSample;
};

#endif // ASSERVSTREAM_H
