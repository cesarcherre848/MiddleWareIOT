#ifndef MQTTCOMM_GLOBAL_H
#define MQTTCOMM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MQTTCOMM_LIBRARY)
#  define MQTTCOMM_EXPORT Q_DECL_EXPORT
#else
#  define MQTTCOMM_EXPORT Q_DECL_IMPORT
#endif

#endif // MQTTCOMM_GLOBAL_H
