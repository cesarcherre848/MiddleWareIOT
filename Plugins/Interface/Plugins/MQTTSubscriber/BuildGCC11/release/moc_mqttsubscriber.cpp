/****************************************************************************
** Meta object code from reading C++ file 'mqttsubscriber.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mqttsubscriber.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mqttsubscriber.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MQTTSubscriber_t {
    const uint offsetsAndSize[14];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MQTTSubscriber_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MQTTSubscriber_t qt_meta_stringdata_MQTTSubscriber = {
    {
QT_MOC_LITERAL(0, 14), // "MQTTSubscriber"
QT_MOC_LITERAL(15, 13), // "recibeSignals"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 13), // "QList<Signal>"
QT_MOC_LITERAL(44, 14), // "computePayload"
QT_MOC_LITERAL(59, 7), // "message"
QT_MOC_LITERAL(67, 5) // "topic"

    },
    "MQTTSubscriber\0recibeSignals\0\0"
    "QList<Signal>\0computePayload\0message\0"
    "topic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MQTTSubscriber[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x08,    1 /* Private */,
       4,    2,   29,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    5,    6,

       0        // eod
};

void MQTTSubscriber::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MQTTSubscriber *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->recibeSignals((*reinterpret_cast< QList<Signal>(*)>(_a[1]))); break;
        case 1: _t->computePayload((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject MQTTSubscriber::staticMetaObject = { {
    QMetaObject::SuperData::link<PluginInterface::staticMetaObject>(),
    qt_meta_stringdata_MQTTSubscriber.offsetsAndSize,
    qt_meta_data_MQTTSubscriber,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MQTTSubscriber_t
, QtPrivate::TypeAndForceComplete<MQTTSubscriber, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QList<Signal>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>


>,
    nullptr
} };


const QMetaObject *MQTTSubscriber::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MQTTSubscriber::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MQTTSubscriber.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "com.mycompany.PluginInterface"))
        return static_cast< PluginInterface*>(this);
    return PluginInterface::qt_metacast(_clname);
}

int MQTTSubscriber::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PluginInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData_MQTTSubscriber[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x1b,  'c',  'o',  'm',  '.',  'e', 
    'x',  'a',  'm',  'p',  'l',  'e',  '.',  'P', 
    'l',  'u',  'g',  'i',  'n',  'I',  'n',  't', 
    'e',  'r',  'f',  'a',  'c',  'e', 
    // "className"
    0x03,  0x6e,  'M',  'Q',  'T',  'T',  'S',  'u', 
    'b',  's',  'c',  'r',  'i',  'b',  'e',  'r', 
    // "MetaData"
    0x04,  0xa1,  0x68,  'M',  'e',  't',  'a',  'D', 
    'a',  't',  'a',  0xa4,  0x66,  'A',  'u',  't', 
    'h',  'o',  'r',  0x70,  'N',  'o',  'm',  'b', 
    'r',  'e',  ' ',  'd',  'e',  'l',  ' ',  'a', 
    'u',  't',  'o',  'r',  0x6b,  'D',  'e',  's', 
    'c',  'r',  'i',  'p',  't',  'i',  'o',  'n', 
    0x71,  'P',  'l',  'u',  'g',  'i',  'n',  ' ', 
    'd',  'e',  ' ',  'e',  'j',  'e',  'm',  'p', 
    'l',  'o',  0x64,  'N',  'a',  'm',  'e',  0x68, 
    'M',  'y',  'P',  'l',  'u',  'g',  'i',  'n', 
    0x67,  'V',  'e',  'r',  's',  'i',  'o',  'n', 
    0x63,  '1',  '.',  '0', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(MQTTSubscriber, MQTTSubscriber)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
