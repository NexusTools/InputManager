#ifndef QDEVICEPROVIDER_H
#define QDEVICEPROVIDER_H

#include <QObject>

class QInputDevice;

class QInputDeviceProvider : public QObject
{
    Q_OBJECT
public:
    explicit QInputDeviceProvider();

signals:
    void deviceFound(QString, QInputDevice*);
    void deviceRemoved(QString);

protected:
    virtual void init() = 0;

private slots:
    void registerWithManager();
    
};

#endif // QDEVICEPROVIDER_H
