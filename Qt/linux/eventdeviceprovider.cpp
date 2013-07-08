#include "eventdeviceprovider.h"
#include "eventinputdevice.h"

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

void QLinuxEventDeviceProvider::deviceDestroyed(QString eventNode) {
    eventInstances.removeOne(eventNode);
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

    QFile* f = new QFile();
    foreach(QFileInfo file, QDir("/dev/input").entryInfoList(QStringList() <<
                             "event*", QDir::System | QDir::Files, QDir::Name)) {

        QString eventFilePath = file.absoluteFilePath();

        if(eventInstances.contains(eventFilePath))
            continue;

        f->setFileName(eventFilePath);
        if(f->open(QFile::ReadOnly)) {
            QLinuxInputDevice* dev = new QLinuxInputDevice(f);
            connect(dev, SIGNAL(destroyed(QString)), this, SLOT(deviceDestroyed(QString)));
            emit deviceFound(eventFilePath, dev);
            eventInstances << eventFilePath;

            f = new QFile();
        }
    }
    f->deleteLater();
}
