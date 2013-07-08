#ifndef DEVICEPROVIDER_H
#define DEVICEPROVIDER_H

#include "../qinputdeviceprovider.h"

#include <QFileSystemWatcher>
#include <QStringList>

class QLinuxEventDevice;

class QLinuxEventDeviceProvider : public QInputDeviceProvider
{
    Q_OBJECT
protected:
    void init();
    
private slots:
    void rescanEventNodes();
    
private:
    QFileSystemWatcher inputWatcher;
    QStringList eventInstances;
};

#endif // DEVICEPROVIDER_H
