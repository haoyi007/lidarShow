/****************************************************************************
** Meta object code from reading C++ file 'radiatrueshow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../radiatrueshow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'radiatrueshow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_radiaTrueShow_t {
    QByteArrayData data[17];
    char stringdata[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_radiaTrueShow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_radiaTrueShow_t qt_meta_stringdata_radiaTrueShow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "radiaTrueShow"
QT_MOC_LITERAL(1, 14, 8), // "senddata"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "char*"
QT_MOC_LITERAL(4, 30, 6), // "TxData"
QT_MOC_LITERAL(5, 37, 3), // "num"
QT_MOC_LITERAL(6, 41, 19), // "receiveURGDataSlot2"
QT_MOC_LITERAL(7, 61, 4), // "data"
QT_MOC_LITERAL(8, 66, 6), // "whitch"
QT_MOC_LITERAL(9, 73, 15), // "receiveATISlot2"
QT_MOC_LITERAL(10, 89, 4), // "roll"
QT_MOC_LITERAL(11, 94, 5), // "pitch"
QT_MOC_LITERAL(12, 100, 3), // "yaw"
QT_MOC_LITERAL(13, 104, 11), // "current_Yaw"
QT_MOC_LITERAL(14, 116, 19), // "receiveNowAttiSlot2"
QT_MOC_LITERAL(15, 136, 10), // "target_Yaw"
QT_MOC_LITERAL(16, 147, 14) // "connectURGData"

    },
    "radiaTrueShow\0senddata\0\0char*\0TxData\0"
    "num\0receiveURGDataSlot2\0data\0whitch\0"
    "receiveATISlot2\0roll\0pitch\0yaw\0"
    "current_Yaw\0receiveNowAttiSlot2\0"
    "target_Yaw\0connectURGData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_radiaTrueShow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   44,    2, 0x0a /* Public */,
       9,    4,   49,    2, 0x0a /* Public */,
      14,    4,   58,    2, 0x0a /* Public */,
      16,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,   12,   15,
    QMetaType::Void,

       0        // eod
};

void radiaTrueShow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        radiaTrueShow *_t = static_cast<radiaTrueShow *>(_o);
        switch (_id) {
        case 0: _t->senddata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->receiveURGDataSlot2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->receiveATISlot2((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 3: _t->receiveNowAttiSlot2((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 4: _t->connectURGData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (radiaTrueShow::*_t)(char * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&radiaTrueShow::senddata)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject radiaTrueShow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_radiaTrueShow.data,
      qt_meta_data_radiaTrueShow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *radiaTrueShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *radiaTrueShow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_radiaTrueShow.stringdata))
        return static_cast<void*>(const_cast< radiaTrueShow*>(this));
    return QDialog::qt_metacast(_clname);
}

int radiaTrueShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void radiaTrueShow::senddata(char * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
