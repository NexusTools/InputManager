#ifndef QLINUXINPUTDEVICE_H
#define QLINUXINPUTDEVICE_H

#include <QObject>
#include <QSocketNotifier>

#include "../qinputdevice.h"

class QFile;

class QLinuxInputDevice : public QInputDevice
{
    Q_OBJECT

    friend class QLinuxEventDeviceProvider;
public:
    virtual ~QLinuxInputDevice();

    inline QString name() const{return _name;}
    inline quint32 rawDeviceID() const{return *((quint32*)_deviceID);}

signals:
    void powerLevelChanged(float);
    void destroyed(QString);

private slots:
    void readEvents();

private:
    explicit QLinuxInputDevice(int);

    QSocketNotifier notifier;

    QString _name;
    quint16 _deviceID[2];
    float _charge;
    int _node;
    
};

#endif // QINPUTDEVICE_H
