#ifndef QINPUTMANAGER_H
#define QINPUTMANAGER_H

#include "qt_global.h"

#include <QFileSystemWatcher>
#include <QPointer>
#include <QHash>
#include <QMap>

class QInputDevice;

enum QInputDeviceType {
    Mouse,
    Keyboard,
    Gamepad,
    Sensor
};

class QTSHARED_EXPORT QInputManager : public QObject
{
    Q_OBJECT

    typedef QPointer<QInputDevice> QInputDevicePointer;
    typedef QList<QInputDevicePointer> QInputDeviceList;
    typedef QHash<QString, QInputDevicePointer> QInputDeviceNameMap;
    typedef QMap<QInputDeviceType, QInputDeviceList> QInputDeviceListMap;

    friend class QInputDeviceProvider;
public:

    static QInputManager* instance();

    QInputDeviceList inputDevices();
    QInputDeviceList inputDevices(QInputDeviceType t);

signals:
    void deviceFound(QInputDevicePointer);

protected slots:
    void registerDevice(QString, QInputDevice*);
    void deregisterDevice(QString);

private:
    explicit inline QInputManager() {}

    QInputDeviceList devices;
    QInputDeviceListMap devicesByType;
    QInputDeviceNameMap devicesByName;

    static QInputManager* _instance;
};

#endif // QINPUTMANAGER_H
