#include <QtGlobal>

#ifdef Q_OS_LINUX

#include "eventinputdevice.h"

#include <QDebug>
#include <QFile>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>

QLinuxInputDevice::QLinuxInputDevice(int f) : notifier(f, QSocketNotifier::Read)
{
    _node = f;
    connect(&notifier, SIGNAL(activated(int)), this, SLOT(readEvents()));

    char temp[200];

    memset(temp, 0, sizeof(temp));
    if(ioctl(_node, EVIOCGNAME(sizeof(temp)), temp) > 2)
        _name = temp;
    else {
        _name = QString("Unknown");
        perror("evdev ioctl");
    }

    memset(temp, 0, sizeof(temp));
    if(ioctl(_node, EVIOCGID, temp) >= 0) {
        _deviceID[0] = ((input_id*)temp)->vendor;
        _deviceID[1] = ((input_id*)temp)->product;
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

    //readEvents();
}

void QLinuxInputDevice::readEvents() {
    qDebug() << "Reading events" << _name;

    input_event event;
    while(read(_node,&event,sizeof(struct input_event)) == sizeof(input_event))
        qDebug() << "Event" << event.type << event.code << event.value;

}

QLinuxInputDevice::~QLinuxInputDevice() {
    qDebug() << _name << "Destroyed";

    close(_node);
}

#endif
