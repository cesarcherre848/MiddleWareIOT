/****************************************************************************
** Meta object code from reading C++ file 'baseservice.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../DataManagerLib/Services/baseservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baseservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BaseService_t {
    const uint offsetsAndSize[14];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_BaseService_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_BaseService_t qt_meta_stringdata_BaseService = {
    {
QT_MOC_LITERAL(0, 11), // "BaseService"
QT_MOC_LITERAL(12, 22), // "returnDataToInputQueue"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 6), // "Signal"
QT_MOC_LITERAL(43, 19), // "finishedLoadPlugins"
QT_MOC_LITERAL(63, 19), // "reciveProcessedData"
QT_MOC_LITERAL(83, 7) // "execute"

    },
    "BaseService\0returnDataToInputQueue\0\0"
    "Signal\0finishedLoadPlugins\0"
    "reciveProcessedData\0execute"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseService[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       4,    0,   41,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   42,    2, 0x0a,    4 /* Public */,
       6,    0,   45,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

       0        // eod
};

void BaseService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseService *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->returnDataToInputQueue((*reinterpret_cast< const Signal(*)>(_a[1]))); break;
        case 1: _t->finishedLoadPlugins(); break;
        case 2: _t->reciveProcessedData((*reinterpret_cast< const Signal(*)>(_a[1]))); break;
        case 3: _t->execute(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BaseService::*)(const Signal & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseService::returnDataToInputQueue)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BaseService::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseService::finishedLoadPlugins)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject BaseService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BaseService.offsetsAndSize,
    qt_meta_data_BaseService,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_BaseService_t
, QtPrivate::TypeAndForceComplete<BaseService, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Signal &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Signal &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *BaseService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BaseService.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BaseService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BaseService::returnDataToInputQueue(const Signal & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BaseService::finishedLoadPlugins()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
