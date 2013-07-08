#include <QtGlobal>

#ifdef XINPUT_SUPPORT

#include "xinputdeviceprovider.h"
#include "../qinputmanager.h"

QLinuxXInputDeviceProvider::QLinuxXInputDeviceProvider(QObject *parent) :
    QInputDeviceProvider(parent)
{
}

QInputManager::registerProvider(new QLinuxXInputDeviceProvider());

#endif
