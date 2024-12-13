/****************************************************************************
** Meta object code from reading C++ file 'processor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../DataManagerLib/Services/processor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Processor_t {
    const uint offsetsAndSize[10];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Processor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Processor_t qt_meta_stringdata_Processor = {
    {
QT_MOC_LITERAL(0, 9), // "Processor"
QT_MOC_LITERAL(10, 14), // "newProcessData"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 6), // "Signal"
QT_MOC_LITERAL(33, 7) // "execute"

    },
    "Processor\0newProcessData\0\0Signal\0"
    "execute"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Processor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   29,    2, 0x0a,    3 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Processor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Processor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newProcessData((*reinterpret_cast< const Signal(*)>(_a[1]))); break;
        case 1: _t->execute(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Processor::*)(const Signal & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Processor::newProcessData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Processor::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseService::staticMetaObject>(),
    qt_meta_stringdata_Processor.offsetsAndSize,
    qt_meta_data_Processor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Processor_t
, QtPrivate::TypeAndForceComplete<Processor, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Signal &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Processor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Processor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Processor.stringdata0))
        return static_cast<void*>(this);
    return BaseService::qt_metacast(_clname);
}

int Processor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseService::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Processor::newProcessData(const Signal & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
