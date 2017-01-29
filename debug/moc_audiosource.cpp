/****************************************************************************
** Meta object code from reading C++ file 'audiosource.h'
**
** Created: Wed 4. Mar 20:30:39 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../audiosource.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audiosource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AudioSource[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   13,   12,   12, 0x0a,
      41,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AudioSource[] = {
    "AudioSource\0\0offset\0setVolumeOffset(int)\0"
    "dataReady()\0"
};

void AudioSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AudioSource *_t = static_cast<AudioSource *>(_o);
        switch (_id) {
        case 0: _t->setVolumeOffset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->dataReady(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AudioSource::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AudioSource::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_AudioSource,
      qt_meta_data_AudioSource, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioSource::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioSource::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioSource))
        return static_cast<void*>(const_cast< AudioSource*>(this));
    return QThread::qt_metacast(_clname);
}

int AudioSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
