/****************************************************************************
** Meta object code from reading C++ file 'eventdispatcher.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../App/Services/EventDispatcher/eventdispatcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eventdispatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EventDispatcher_t {
    const uint offsetsAndSize[16];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_EventDispatcher_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_EventDispatcher_t qt_meta_stringdata_EventDispatcher = {
    {
QT_MOC_LITERAL(0, 15), // "EventDispatcher"
QT_MOC_LITERAL(16, 23), // "updateAssignedComponent"
QT_MOC_LITERAL(40, 0), // ""
QT_MOC_LITERAL(41, 14), // "computePayload"
QT_MOC_LITERAL(56, 7), // "message"
QT_MOC_LITERAL(64, 5), // "topic"
QT_MOC_LITERAL(70, 18), // "reciveUpdateAction"
QT_MOC_LITERAL(89, 12) // "ActionUpdate"

    },
    "EventDispatcher\0updateAssignedComponent\0"
    "\0computePayload\0message\0topic\0"
    "reciveUpdateAction\0ActionUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EventDispatcher[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    2,   33,    2, 0x08,    2 /* Private */,
       6,    1,   38,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void EventDispatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EventDispatcher *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateAssignedComponent(); break;
        case 1: _t->computePayload((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->reciveUpdateAction((*reinterpret_cast< ActionUpdate(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EventDispatcher::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EventDispatcher::updateAssignedComponent)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject EventDispatcher::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_EventDispatcher.offsetsAndSize,
    qt_meta_data_EventDispatcher,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_EventDispatcher_t
, QtPrivate::TypeAndForceComplete<EventDispatcher, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ActionUpdate, std::false_type>


>,
    nullptr
} };


const QMetaObject *EventDispatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EventDispatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EventDispatcher.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EventDispatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void EventDispatcher::updateAssignedComponent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
