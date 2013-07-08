#include "qinputdeviceprovider.h"
#include "qinputmanager.h"
#include "qinputdevice.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>
#include <QDir>

QInputManager* QInputManager::_instance = 0;

QInputManager* QInputManager::instance() {
    if(!_instance)
        _instance = new QInputManager();
    return _instance;
}

void QInputManager::registerDevice(QString name, QInputDevice* dev) {
    Q_ASSERT(sender());
    Q_ASSERT(dev != 0);

    QString realName = QString("%1:%2").arg(sender()->metaObject()->className()).arg(name);
    qDebug() << "Registering" << realName << dev->name();

    QInputDevice* old = devicesByName.take(realName);
    if(old) {
        qWarning() << "Replacing existing";
        old->deleteLater();
    }

    devicesByName.insert(realName, dev);
    emit deviceFound(dev);
}

void QInputManager::deregisterDevice(QString name) {
    Q_ASSERT(sender());

    QString realName = QString("%1:%2").arg(sender()->metaObject()->className()).arg(name);

    QInputDevice* dev = devicesByName.take(realName);
    if(!dev)
        qWarning() << "No such device registered" << realName;
    else {
        qDebug() << "De-registering" << realName << dev->name();
        dev->deleteLater();
    }
}

QInputDeviceProvider::QInputDeviceProvider() {
    QTimer::singleShot(0, this, SLOT(registerWithManager()));
}

void QInputDeviceProvider::registerWithManager() {
    qDebug() << "Registered" << this->metaObject()->className();
    connect(this, SIGNAL(deviceFound(QString,QInputDevice*)), QInputManager::instance(), SLOT(registerDevice(QString,QInputDevice*)));
    connect(this, SIGNAL(deviceRemoved(QString)), QInputManager::instance(), SLOT(deregisterDevice(QString)));
    init();
}

#ifndef QT_LIBRARY
int main(int argc, char **argv) {
    QCoreApplication core(argc, argv);
    QInputManager::instance();
    return core.exec();
}
#endif
