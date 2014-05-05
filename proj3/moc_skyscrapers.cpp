/****************************************************************************
** Meta object code from reading C++ file 'skyscrapers.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "skyscrapers.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skyscrapers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Skyscrapers_t {
    QByteArrayData data[10];
    char stringdata[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Skyscrapers_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Skyscrapers_t qt_meta_stringdata_Skyscrapers = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 15),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 15),
QT_MOC_LITERAL(4, 45, 14),
QT_MOC_LITERAL(5, 60, 15),
QT_MOC_LITERAL(6, 76, 13),
QT_MOC_LITERAL(7, 90, 14),
QT_MOC_LITERAL(8, 105, 14),
QT_MOC_LITERAL(9, 120, 14)
    },
    "Skyscrapers\0slotCheckButton\0\0"
    "slotClearButton\0slotHintButton\0"
    "slotSolveButton\0slotTryButton\0"
    "slotUndoButton\0slotGridButton\0"
    "slotLoadButton\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Skyscrapers[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08,
       3,    0,   55,    2, 0x08,
       4,    0,   56,    2, 0x08,
       5,    0,   57,    2, 0x08,
       6,    0,   58,    2, 0x08,
       7,    0,   59,    2, 0x08,
       8,    0,   60,    2, 0x08,
       9,    0,   61,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Skyscrapers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Skyscrapers *_t = static_cast<Skyscrapers *>(_o);
        switch (_id) {
        case 0: _t->slotCheckButton(); break;
        case 1: _t->slotClearButton(); break;
        case 2: _t->slotHintButton(); break;
        case 3: _t->slotSolveButton(); break;
        case 4: _t->slotTryButton(); break;
        case 5: _t->slotUndoButton(); break;
        case 6: _t->slotGridButton(); break;
        case 7: _t->slotLoadButton(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Skyscrapers::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Skyscrapers.data,
      qt_meta_data_Skyscrapers,  qt_static_metacall, 0, 0}
};


const QMetaObject *Skyscrapers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Skyscrapers::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Skyscrapers.stringdata))
        return static_cast<void*>(const_cast< Skyscrapers*>(this));
    return QWidget::qt_metacast(_clname);
}

int Skyscrapers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
