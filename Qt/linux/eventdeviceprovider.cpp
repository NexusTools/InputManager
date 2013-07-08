#include "eventdeviceprovider.h"
#include "eventinputdevice.h"

#include <unistd.h>
#include <fcntl.h>

#include <QFileInfo>
#include <QTimer>
#include <QFile>
#include <QHash>
#include <QDir>

QLinuxEventDeviceProvider __linuxEventDeviceProvider__instance;

void QLinuxEventDeviceProvider::init()
{
    inputWatcher.addPath("/dev/input");
    connect(&inputWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(rescanEventNodes()));

    QTimer::singleShot(0, this, SLOT(rescanEventNodes()));
}

void QLinuxEventDeviceProvider::rescanEventNodes() {
    QStringList::iterator i = eventInstances.begin();
    while(i != eventInstances.end()) {
        if(!QFileInfo(*i).exists()) {
            emit deviceRemoved(*i);
            i = eventInstances.erase(i);
        } else
            i++;
    }

    int node;
    foreach(QFileInfo file, QDir("/dev/input").entryInfoList(QStringList() <<
                             "event*", QDir::System | QDir::Files, QDir::Name)) {

        QString eventFilePath = file.absoluteFilePath();

        if(eventInstances.contains(eventFilePath))
            continue;

        node = open(eventFilePath.toLocal8Bit().data(), O_RDONLY);
        if(node > -1) {
            QLinuxInputDevice* dev = new QLinuxInputDevice(node);
            emit deviceFound(eventFilePath, dev);
            eventInstances << eventFilePath;
        }
    }
}
