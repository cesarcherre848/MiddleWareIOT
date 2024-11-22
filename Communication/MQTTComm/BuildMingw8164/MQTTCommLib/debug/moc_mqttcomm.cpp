/****************************************************************************
** Meta object code from reading C++ file 'mqttcomm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../MQTTCommLib/mqttcomm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mqttcomm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MQTTComm_t {
    const uint offsetsAndSize[24];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MQTTComm_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MQTTComm_t qt_meta_stringdata_MQTTComm = {
    {
QT_MOC_LITERAL(0, 8), // "MQTTComm"
QT_MOC_LITERAL(9, 22), // "updateStatusConnection"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 14), // "recievePayload"
QT_MOC_LITERAL(48, 7), // "message"
QT_MOC_LITERAL(56, 5), // "topic"
QT_MOC_LITERAL(62, 11), // "onConnected"
QT_MOC_LITERAL(74, 14), // "onStateChanged"
QT_MOC_LITERAL(89, 24), // "QMqttClient::ClientState"
QT_MOC_LITERAL(114, 5), // "state"
QT_MOC_LITERAL(120, 14), // "onDisconnected"
QT_MOC_LITERAL(135, 12) // "tryReconnect"

    },
    "MQTTComm\0updateStatusConnection\0\0"
    "recievePayload\0message\0topic\0onConnected\0"
    "onStateChanged\0QMqttClient::ClientState\0"
    "state\0onDisconnected\0tryReconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MQTTComm[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       3,    2,   53,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   58,    2, 0x0a,    6 /* Public */,
       7,    1,   59,    2, 0x0a,    7 /* Public */,
      10,    0,   62,    2, 0x0a,    9 /* Public */,
      11,    0,   63,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MQTTComm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MQTTComm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateStatusConnection((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->recievePayload((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->onConnected(); break;
        case 3: _t->onStateChanged((*reinterpret_cast< QMqttClient::ClientState(*)>(_a[1]))); break;
        case 4: _t->onDisconnected(); break;
        case 5: _t->tryReconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QMqttClient::ClientState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MQTTComm::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MQTTComm::updateStatusConnection)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MQTTComm::*)(const QByteArray & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MQTTComm::recievePayload)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MQTTComm::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MQTTComm.offsetsAndSize,
    qt_meta_data_MQTTComm,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MQTTComm_t
, QtPrivate::TypeAndForceComplete<MQTTComm, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMqttClient::ClientState, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MQTTComm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MQTTComm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MQTTComm.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MQTTComm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MQTTComm::updateStatusConnection(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MQTTComm::recievePayload(const QByteArray & _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
