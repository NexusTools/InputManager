#ifndef QLINUXINPUTDEVICE_H
#define QLINUXINPUTDEVICE_H

#include <QObject>

#include "../qinputdevice.h"

class QFile;

class QLinuxInputDevice : public QInputDevice
{
    Q_OBJECT

    friend class QLinuxEventDeviceProvider;
public:
    virtual ~QLinuxInputDevice();

    inline QString name() const{return _name;}
    inline quint32 rawDeviceID() const{return _deviceID;}

signals:
    void powerLevelChanged(float);
    void destroyed(QString);

private slots:
    void readEvents();

private:
    explicit QLinuxInputDevice(QFile*);

    QString _name;
    quint32 _deviceID;
    float _charge;
    QFile* _node;
    
};

#endif // QINPUTDEVICE_H
