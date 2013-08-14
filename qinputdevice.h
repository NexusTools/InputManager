#ifndef QINPUTDEVICE_H
#define QINPUTDEVICE_H

#include <QPointer>

class QInputDevice : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(quint16 vender READ vender)
    Q_PROPERTY(quint16 product READ product)
    Q_PROPERTY(float chargeLevel READ chargeLevel)
public:

    virtual inline QString name() const{return "Unknown";}

    inline quint16 vender() const{return (quint16)rawDeviceID();}
    inline quint16 product() const{return rawDeviceID();}

    Q_INVOKABLE inline QByteArray deviceID() const{return QByteArray::number(rawDeviceID()).toHex();}
    Q_INVOKABLE virtual inline quint32 rawDeviceID() const{return 0;}

    Q_INVOKABLE inline bool hasChargeLevel() const{return chargeLevel() > -1;}
    Q_INVOKABLE virtual inline bool isCharging() const{return false;}
    virtual inline float chargeLevel() const{return -1;}
    
};

typedef QPointer<QInputDevice> QInputDevicePointer;

#endif // QINPUTDEVICE_H
