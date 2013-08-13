#-------------------------------------------------
#
# Project created by QtCreator 2013-07-08T10:38:33
#
#-------------------------------------------------

QT       -= gui

TARGET = InputManager
contains(CONFIG, standalone) {
	TEMPLATE = app
} else {
	TEMPLATE = lib
	DEFINES += QT_LIBRARY

	unix:!symbian {
		maemo5 {
			target.path = /opt/usr/lib
		} else {
			target.path = /usr/lib
		}
		INSTALLS += target
	}
}


SOURCES += qinputmanager.cpp \
    linux/eventdeviceprovider.cpp \
    x11/xinputdeviceprovider.cpp \
    linux/eventinputdevice.cpp

HEADERS += qinputmanager.h\
        qt_global.h \
    qinputdevice.h \
    linux/eventdeviceprovider.h \
    qinputdeviceprovider.h \
    x11/xinputdeviceprovider.h \
    linux/eventinputdevice.h


