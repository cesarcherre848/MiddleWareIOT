/****************************************************************************
** Meta object code from reading C++ file 'array2dstatistics.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../array2dstatistics.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'array2dstatistics.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Array2DStatistics_t {
    const uint offsetsAndSize[2];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Array2DStatistics_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Array2DStatistics_t qt_meta_stringdata_Array2DStatistics = {
    {
QT_MOC_LITERAL(0, 17) // "Array2DStatistics"

    },
    "Array2DStatistics"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Array2DStatistics[] = {

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

void Array2DStatistics::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject Array2DStatistics::staticMetaObject = { {
    QMetaObject::SuperData::link<PluginInterface::staticMetaObject>(),
    qt_meta_stringdata_Array2DStatistics.offsetsAndSize,
    qt_meta_data_Array2DStatistics,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Array2DStatistics_t
, QtPrivate::TypeAndForceComplete<Array2DStatistics, std::true_type>



>,
    nullptr
} };


const QMetaObject *Array2DStatistics::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Array2DStatistics::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Array2DStatistics.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "com.mycompany.PluginInterface"))
        return static_cast< PluginInterface*>(this);
    return PluginInterface::qt_metacast(_clname);
}

int Array2DStatistics::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PluginInterface::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData_Array2DStatistics[] = {
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
    0x03,  0x71,  'A',  'r',  'r',  'a',  'y',  '2', 
    'D',  'S',  't',  'a',  't',  'i',  's',  't', 
    'i',  'c',  's', 
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
QT_MOC_EXPORT_PLUGIN(Array2DStatistics, Array2DStatistics)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
