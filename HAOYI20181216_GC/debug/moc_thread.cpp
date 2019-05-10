/****************************************************************************
** Meta object code from reading C++ file 'thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Thread_t {
    QByteArrayData data[23];
    char stringdata[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Thread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Thread_t qt_meta_stringdata_Thread = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Thread"
QT_MOC_LITERAL(1, 7, 9), // "sendATIOk"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 4), // "roll"
QT_MOC_LITERAL(4, 23, 5), // "pitch"
QT_MOC_LITERAL(5, 29, 3), // "yaw"
QT_MOC_LITERAL(6, 33, 11), // "current_Yaw"
QT_MOC_LITERAL(7, 45, 13), // "send_Now_Atti"
QT_MOC_LITERAL(8, 59, 10), // "target_Yaw"
QT_MOC_LITERAL(9, 70, 21), // "send_Air_Rec_Commatti"
QT_MOC_LITERAL(10, 92, 11), // "sendURGData"
QT_MOC_LITERAL(11, 104, 4), // "data"
QT_MOC_LITERAL(12, 109, 9), // "whitchnum"
QT_MOC_LITERAL(13, 119, 16), // "transReceiveData"
QT_MOC_LITERAL(14, 136, 11), // "requestData"
QT_MOC_LITERAL(15, 148, 19), // "transTargetPosition"
QT_MOC_LITERAL(16, 168, 3), // "lat"
QT_MOC_LITERAL(17, 172, 3), // "lon"
QT_MOC_LITERAL(18, 176, 12), // "sendDateSlot"
QT_MOC_LITERAL(19, 189, 5), // "char*"
QT_MOC_LITERAL(20, 195, 6), // "TxData"
QT_MOC_LITERAL(21, 202, 3), // "num"
QT_MOC_LITERAL(22, 206, 9) // "read_Data"

    },
    "Thread\0sendATIOk\0\0roll\0pitch\0yaw\0"
    "current_Yaw\0send_Now_Atti\0target_Yaw\0"
    "send_Air_Rec_Commatti\0sendURGData\0"
    "data\0whitchnum\0transReceiveData\0"
    "requestData\0transTargetPosition\0lat\0"
    "lon\0sendDateSlot\0char*\0TxData\0num\0"
    "read_Data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Thread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   54,    2, 0x06 /* Public */,
       7,    4,   63,    2, 0x06 /* Public */,
       9,    3,   72,    2, 0x06 /* Public */,
      10,    2,   79,    2, 0x06 /* Public */,
      13,    1,   84,    2, 0x06 /* Public */,
      15,    2,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    2,   92,    2, 0x0a /* Public */,
      22,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,    8,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::QByteArray,   14,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   16,   17,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 19, QMetaType::Int,   20,   21,
    QMetaType::Void,

       0        // eod
};

void Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Thread *_t = static_cast<Thread *>(_o);
        switch (_id) {
        case 0: _t->sendATIOk((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 1: _t->send_Now_Atti((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 2: _t->send_Air_Rec_Commatti((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 3: _t->sendURGData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->transReceiveData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->transTargetPosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->sendDateSlot((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->read_Data(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Thread::*_t)(float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thread::sendATIOk)) {
                *result = 0;
            }
        }
        {
            typedef void (Thread::*_t)(float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thread::send_Now_Atti)) {
                *result = 1;
            }
        }
        {
            typedef void (Thread::*_t)(float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thread::send_Air_Rec_Commatti)) {
                *result = 2;
            }
        }
        {
            typedef void (Thread::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thread::sendURGData)) {
                *result = 3;
            }
        }
        {
            typedef void (Thread::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thread::transReceiveData)) {
                *result = 4;
            }
        }
        {
            typedef void (Thread::*_t)(float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thread::transTargetPosition)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject Thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Thread.data,
      qt_meta_data_Thread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Thread.stringdata))
        return static_cast<void*>(const_cast< Thread*>(this));
    return QThread::qt_metacast(_clname);
}

int Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void Thread::sendATIOk(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Thread::send_Now_Atti(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Thread::send_Air_Rec_Commatti(float _t1, float _t2, float _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Thread::sendURGData(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Thread::transReceiveData(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Thread::transTargetPosition(float _t1, float _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
