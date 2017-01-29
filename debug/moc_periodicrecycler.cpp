/****************************************************************************
** Meta object code from reading C++ file 'periodicrecycler.h'
**
** Created: Sun 3. Apr 23:07:32 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../periodicrecycler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'periodicrecycler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PeriodicRecycler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   17,   17,   17, 0x08,
      54,   46,   17,   17, 0x0a,
      71,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PeriodicRecycler[] = {
    "PeriodicRecycler\0\0timeToRecycle()\0"
    "checkTime()\0enabled\0setEnabled(bool)\0"
    "performRecycle()\0"
};

void PeriodicRecycler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PeriodicRecycler *_t = static_cast<PeriodicRecycler *>(_o);
        switch (_id) {
        case 0: _t->timeToRecycle(); break;
        case 1: _t->checkTime(); break;
        case 2: _t->setEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->performRecycle(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PeriodicRecycler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PeriodicRecycler::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PeriodicRecycler,
      qt_meta_data_PeriodicRecycler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PeriodicRecycler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PeriodicRecycler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PeriodicRecycler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PeriodicRecycler))
        return static_cast<void*>(const_cast< PeriodicRecycler*>(this));
    return QThread::qt_metacast(_clname);
}

int PeriodicRecycler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void PeriodicRecycler::timeToRecycle()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
