#ifndef QT_GLOBAL_H
#define QT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QT_LIBRARY)
#  define QTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QT_GLOBAL_H
