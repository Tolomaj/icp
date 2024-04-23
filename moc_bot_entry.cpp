/****************************************************************************
** Meta object code from reading C++ file 'bot_entry.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "bot_entry.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bot_entry.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BOT_Entry_t {
    QByteArrayData data[5];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BOT_Entry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BOT_Entry_t qt_meta_stringdata_BOT_Entry = {
    {
QT_MOC_LITERAL(0, 0, 9), // "BOT_Entry"
QT_MOC_LITERAL(1, 10, 10), // "goButton_f"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "leftButton_f"
QT_MOC_LITERAL(4, 35, 13) // "rightButton_f"

    },
    "BOT_Entry\0goButton_f\0\0leftButton_f\0"
    "rightButton_f"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BOT_Entry[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BOT_Entry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BOT_Entry *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->goButton_f(); break;
        case 1: _t->leftButton_f(); break;
        case 2: _t->rightButton_f(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject BOT_Entry::staticMetaObject = { {
    QMetaObject::SuperData::link<Entry::staticMetaObject>(),
    qt_meta_stringdata_BOT_Entry.data,
    qt_meta_data_BOT_Entry,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BOT_Entry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BOT_Entry::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BOT_Entry.stringdata0))
        return static_cast<void*>(this);
    return Entry::qt_metacast(_clname);
}

int BOT_Entry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Entry::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
