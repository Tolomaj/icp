/****************************************************************************
** Meta object code from reading C++ file 'mediator.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mediator.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mediator.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mediator_t {
    QByteArrayData data[24];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mediator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mediator_t qt_meta_stringdata_Mediator = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Mediator"
QT_MOC_LITERAL(1, 9, 19), // "notify_registartion"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "ObjectType"
QT_MOC_LITERAL(4, 41, 4), // "type"
QT_MOC_LITERAL(5, 46, 29), // "notify_forvarded_registartion"
QT_MOC_LITERAL(6, 76, 2), // "id"
QT_MOC_LITERAL(7, 79, 21), // "notify_unregistration"
QT_MOC_LITERAL(8, 101, 20), // "notify_states_change"
QT_MOC_LITERAL(9, 122, 9), // "RoboState"
QT_MOC_LITERAL(10, 132, 5), // "state"
QT_MOC_LITERAL(11, 138, 11), // "notify_move"
QT_MOC_LITERAL(12, 150, 1), // "x"
QT_MOC_LITERAL(13, 152, 1), // "y"
QT_MOC_LITERAL(14, 154, 8), // "rotation"
QT_MOC_LITERAL(15, 163, 19), // "notify_bot_controll"
QT_MOC_LITERAL(16, 183, 14), // "ControllComand"
QT_MOC_LITERAL(17, 198, 7), // "command"
QT_MOC_LITERAL(18, 206, 26), // "notify_simulation_controll"
QT_MOC_LITERAL(19, 233, 12), // "SimuControll"
QT_MOC_LITERAL(20, 246, 16), // "notify_send_save"
QT_MOC_LITERAL(21, 263, 6), // "FileOP"
QT_MOC_LITERAL(22, 270, 14), // "file_operation"
QT_MOC_LITERAL(23, 285, 4) // "path"

    },
    "Mediator\0notify_registartion\0\0ObjectType\0"
    "type\0notify_forvarded_registartion\0"
    "id\0notify_unregistration\0notify_states_change\0"
    "RoboState\0state\0notify_move\0x\0y\0"
    "rotation\0notify_bot_controll\0"
    "ControllComand\0command\0"
    "notify_simulation_controll\0SimuControll\0"
    "notify_send_save\0FileOP\0file_operation\0"
    "path"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mediator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    2,   57,    2, 0x06 /* Public */,
       7,    1,   62,    2, 0x06 /* Public */,
       8,    2,   65,    2, 0x06 /* Public */,
      11,    4,   70,    2, 0x06 /* Public */,
      15,    2,   79,    2, 0x06 /* Public */,
      18,    1,   84,    2, 0x06 /* Public */,
      20,    2,   87,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    6,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    6,   12,   13,   14,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,    6,   17,
    QMetaType::Void, 0x80000000 | 19,   17,
    QMetaType::Void, 0x80000000 | 21, QMetaType::QString,   22,   23,

       0        // eod
};

void Mediator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Mediator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->notify_registartion((*reinterpret_cast< ObjectType(*)>(_a[1]))); break;
        case 1: _t->notify_forvarded_registartion((*reinterpret_cast< ObjectType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->notify_unregistration((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->notify_states_change((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< RoboState(*)>(_a[2]))); break;
        case 4: _t->notify_move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->notify_bot_controll((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ControllComand(*)>(_a[2]))); break;
        case 6: _t->notify_simulation_controll((*reinterpret_cast< SimuControll(*)>(_a[1]))); break;
        case 7: _t->notify_send_save((*reinterpret_cast< FileOP(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Mediator::*)(ObjectType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mediator::notify_registartion)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Mediator::*)(ObjectType , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mediator::notify_forvarded_registartion)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Mediator::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mediator::notify_unregistration)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Mediator::*)(int , RoboState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mediator::notify_states_change)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Mediator::*)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mediator::notify_move)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Mediator::*)(int , ControllComand );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mediator::notify_bot_controll)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Mediator::*)(SimuControll );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mediator::notify_simulation_controll)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Mediator::*)(FileOP , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mediator::notify_send_save)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mediator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Mediator.data,
    qt_meta_data_Mediator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Mediator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mediator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mediator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Mediator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Mediator::notify_registartion(ObjectType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mediator::notify_forvarded_registartion(ObjectType _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mediator::notify_unregistration(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Mediator::notify_states_change(int _t1, RoboState _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Mediator::notify_move(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Mediator::notify_bot_controll(int _t1, ControllComand _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Mediator::notify_simulation_controll(SimuControll _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Mediator::notify_send_save(FileOP _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
