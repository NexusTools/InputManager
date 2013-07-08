#include <QtGlobal>

#ifdef Q_OS_LINUX

#include "eventinputdevice.h"

#include <QDebug>
#include <QFile>

#include <stdio.h>
#include <linux/input.h>

QLinuxInputDevice::QLinuxInputDevice(QFile *f)
{
    _node = f;
    connect(_node, SIGNAL(destroyed()), this, SLOT(deleteLater()));
    connect(_node, SIGNAL(readChannelFinished()), this, SLOT(deleteLater()));
    connect(_node, SIGNAL(aboutToClose()), this, SLOT(deleteLater()));
    connect(_node, SIGNAL(readyRead()), this, SLOT(readEvents()));

    char temp[200];

    memset(temp, 0, sizeof(temp));
    if(ioctl(_node->handle(), EVIOCGNAME(sizeof(temp)), temp) > 2)
        _name = temp;
    else {
        _name = QString("Unknown (%1)").arg(f->fileName());
        perror("evdev ioctl");
    }

    memset(temp, 0, sizeof(temp));
    if(ioctl(_node->handle(), EVIOCGID, temp) >= 0) {
        //*((quint16*)&_deviceID) = ((input_id*)temp)->vendor;
        //*((quint16*)(&_deviceID + 2)) = ((input_id*)temp)->product;
    } else
        perror("evdev ioctl");

    /*memset(temp, 0, sizeof(temp));
    if(ioctl(f.handle(), EVIOCGPROP(sizeof(temp)), temp) >= 0) {
        qDebug() << "Properties" << temp;
    } else
        perror("evdev ioctl");

    memset(temp, 0, sizeof(temp));
    if(ioctl(f.handle(), EVIOCGBIT(0, EV_MAX), temp) >= 0) {
        qDebug() << "Capabilities" << QByteArray(temp, EV_MAX/8).toHex();
    } else
        perror("evdev ioctl");*/

    readEvents();
}

void QLinuxInputDevice::readEvents() {
    qDebug() << "Reading events" << _node->bytesAvailable();

    input_event event;
    while(_node->bytesAvailable() >= sizeof(input_event)) {
        if(_node->read((char*)&event, sizeof(input_event)) != sizeof(input_event)) {
            deleteLater();
            break;
        }
        qDebug() << "Event" << event.type << event.code << event.value;
    }
}

QLinuxInputDevice::~QLinuxInputDevice() {
    qDebug() << _name << "Destroyed";
    emit destroyed(_node->fileName());

    _node->close();
    delete _node;
}

#endif
