/****************************************************************************
** Meta object code from reading C++ file 'basicstatistics.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../basicstatistics.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basicstatistics.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BasicStatistics_t {
    const uint offsetsAndSize[2];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_BasicStatistics_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_BasicStatistics_t qt_meta_stringdata_BasicStatistics = {
    {
QT_MOC_LITERAL(0, 15) // "BasicStatistics"

    },
    "BasicStatistics"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BasicStatistics[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void BasicStatistics::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject BasicStatistics::staticMetaObject = { {
    QMetaObject::SuperData::link<PluginInterface::staticMetaObject>(),
    qt_meta_stringdata_BasicStatistics.offsetsAndSize,
    qt_meta_data_BasicStatistics,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_BasicStatistics_t
, QtPrivate::TypeAndForceComplete<BasicStatistics, std::true_type>



>,
    nullptr
} };


const QMetaObject *BasicStatistics::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BasicStatistics::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BasicStatistics.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "com.mycompany.PluginInterface"))
        return static_cast< PluginInterface*>(this);
    return PluginInterface::qt_metacast(_clname);
}

int BasicStatistics::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PluginInterface::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData_BasicStatistics[] = {
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
    0x03,  0x6f,  'B',  'a',  's',  'i',  'c',  'S', 
    't',  'a',  't',  'i',  's',  't',  'i',  'c', 
    's', 
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
QT_MOC_EXPORT_PLUGIN(BasicStatistics, BasicStatistics)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
