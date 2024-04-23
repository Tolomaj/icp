/****************************************************************************
** Meta object code from reading C++ file 'Testing_object.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Testing_object.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Testing_object.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Test_Probe_t {
    QByteArrayData data[24];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Test_Probe_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Test_Probe_t qt_meta_stringdata_Test_Probe = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Test_Probe"
QT_MOC_LITERAL(1, 11, 8), // "tstFiles"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "FileOP"
QT_MOC_LITERAL(4, 28, 9), // "operation"
QT_MOC_LITERAL(5, 38, 3), // "str"
QT_MOC_LITERAL(6, 42, 14), // "tstSimControll"
QT_MOC_LITERAL(7, 57, 12), // "SimuControll"
QT_MOC_LITERAL(8, 70, 7), // "command"
QT_MOC_LITERAL(9, 78, 9), // "tstRemove"
QT_MOC_LITERAL(10, 88, 2), // "id"
QT_MOC_LITERAL(11, 91, 7), // "tstMove"
QT_MOC_LITERAL(12, 99, 1), // "x"
QT_MOC_LITERAL(13, 101, 1), // "y"
QT_MOC_LITERAL(14, 103, 1), // "r"
QT_MOC_LITERAL(15, 105, 8), // "tstState"
QT_MOC_LITERAL(16, 114, 9), // "RoboState"
QT_MOC_LITERAL(17, 124, 5), // "state"
QT_MOC_LITERAL(18, 130, 17), // "tstFWregistration"
QT_MOC_LITERAL(19, 148, 10), // "ObjectType"
QT_MOC_LITERAL(20, 159, 5), // "bject"
QT_MOC_LITERAL(21, 165, 15), // "tstregistration"
QT_MOC_LITERAL(22, 181, 11), // "tstControll"
QT_MOC_LITERAL(23, 193, 14) // "ControllComand"

    },
    "Test_Probe\0tstFiles\0\0FileOP\0operation\0"
    "str\0tstSimControll\0SimuControll\0command\0"
    "tstRemove\0id\0tstMove\0x\0y\0r\0tstState\0"
    "RoboState\0state\0tstFWregistration\0"
    "ObjectType\0bject\0tstregistration\0"
    "tstControll\0ControllComand"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Test_Probe[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x0a /* Public */,
       6,    1,   59,    2, 0x0a /* Public */,
       9,    1,   62,    2, 0x0a /* Public */,
      11,    4,   65,    2, 0x0a /* Public */,
      15,    2,   74,    2, 0x0a /* Public */,
      18,    2,   79,    2, 0x0a /* Public */,
      21,    1,   84,    2, 0x0a /* Public */,
      22,    2,   87,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   12,   13,   14,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,   10,   17,
    QMetaType::Void, 0x80000000 | 19, QMetaType::Int,   20,   10,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 23,   10,   20,

       0        // eod
};

void Test_Probe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Test_Probe *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->tstFiles((*reinterpret_cast< FileOP(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->tstSimControll((*reinterpret_cast< SimuControll(*)>(_a[1]))); break;
        case 2: _t->tstRemove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->tstMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: _t->tstState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< RoboState(*)>(_a[2]))); break;
        case 5: _t->tstFWregistration((*reinterpret_cast< ObjectType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->tstregistration((*reinterpret_cast< ObjectType(*)>(_a[1]))); break;
        case 7: _t->tstControll((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ControllComand(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Test_Probe::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Test_Probe.data,
    qt_meta_data_Test_Probe,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Test_Probe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Test_Probe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Test_Probe.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Test_Probe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
