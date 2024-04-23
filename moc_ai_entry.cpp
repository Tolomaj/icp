/****************************************************************************
** Meta object code from reading C++ file 'ai_entry.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ai_entry.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ai_entry.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AI_Entry_t {
    QByteArrayData data[6];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AI_Entry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AI_Entry_t qt_meta_stringdata_AI_Entry = {
    {
QT_MOC_LITERAL(0, 0, 8), // "AI_Entry"
QT_MOC_LITERAL(1, 9, 8), // "setState"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 1), // "i"
QT_MOC_LITERAL(4, 21, 9), // "RoboState"
QT_MOC_LITERAL(5, 31, 5) // "state"

    },
    "AI_Entry\0setState\0\0i\0RoboState\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AI_Entry[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,

       0        // eod
};

void AI_Entry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AI_Entry *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< RoboState(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AI_Entry::staticMetaObject = { {
    QMetaObject::SuperData::link<Entry::staticMetaObject>(),
    qt_meta_stringdata_AI_Entry.data,
    qt_meta_data_AI_Entry,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AI_Entry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AI_Entry::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AI_Entry.stringdata0))
        return static_cast<void*>(this);
    return Entry::qt_metacast(_clname);
}

int AI_Entry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Entry::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
