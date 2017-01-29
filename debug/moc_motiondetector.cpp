/****************************************************************************
** Meta object code from reading C++ file 'motiondetector.h'
**
** Created: Sun 3. Apr 23:18:46 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../motiondetector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'motiondetector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MotionDetector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   16,   15,   15, 0x05,
      43,   15,   15,   15, 0x05,
      57,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MotionDetector[] = {
    "MotionDetector\0\0amount\0motionDetected(int)\0"
    "motionAlert()\0motionCeases()\0"
    "motionStopped()\0"
};

void MotionDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MotionDetector *_t = static_cast<MotionDetector *>(_o);
        switch (_id) {
        case 0: _t->motionDetected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->motionAlert(); break;
        case 2: _t->motionCeases(); break;
        case 3: _t->motionStopped(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MotionDetector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MotionDetector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MotionDetector,
      qt_meta_data_MotionDetector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MotionDetector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MotionDetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MotionDetector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MotionDetector))
        return static_cast<void*>(const_cast< MotionDetector*>(this));
    return QObject::qt_metacast(_clname);
}

int MotionDetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MotionDetector::motionDetected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MotionDetector::motionAlert()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MotionDetector::motionCeases()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
