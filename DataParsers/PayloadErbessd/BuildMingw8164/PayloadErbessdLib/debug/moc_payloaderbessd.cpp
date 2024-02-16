/****************************************************************************
** Meta object code from reading C++ file 'payloaderbessd.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../PayloadErbessdLib/payloaderbessd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'payloaderbessd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PayloadErbessd_t {
    const uint offsetsAndSize[12];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PayloadErbessd_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PayloadErbessd_t qt_meta_stringdata_PayloadErbessd = {
    {
QT_MOC_LITERAL(0, 14), // "PayloadErbessd"
QT_MOC_LITERAL(15, 8), // "finished"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 13), // "updateSignals"
QT_MOC_LITERAL(39, 13), // "QList<Signal>"
QT_MOC_LITERAL(53, 7) // "execute"

    },
    "PayloadErbessd\0finished\0\0updateSignals\0"
    "QList<Signal>\0execute"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PayloadErbessd[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    1 /* Public */,
       3,    1,   33,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   36,    2, 0x0a,    4 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PayloadErbessd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PayloadErbessd *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->updateSignals((*reinterpret_cast< QList<Signal>(*)>(_a[1]))); break;
        case 2: _t->execute(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PayloadErbessd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PayloadErbessd::finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PayloadErbessd::*)(QList<Signal> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PayloadErbessd::updateSignals)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PayloadErbessd::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PayloadErbessd.offsetsAndSize,
    qt_meta_data_PayloadErbessd,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PayloadErbessd_t
, QtPrivate::TypeAndForceComplete<PayloadErbessd, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QList<Signal>, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *PayloadErbessd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PayloadErbessd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PayloadErbessd.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PayloadErbessd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PayloadErbessd::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PayloadErbessd::updateSignals(QList<Signal> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
