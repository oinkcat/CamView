/****************************************************************************
** Meta object code from reading C++ file 'mjpegsource.h'
**
** Created: Sun 3. Apr 23:18:45 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mjpegsource.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mjpegsource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MJPegSource[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,
      45,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   12,   12,   12, 0x0a,
      61,   12,   12,   12, 0x08,
      85,   79,   12,   12, 0x08,
     122,   12,   12,   12, 0x08,
     135,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MJPegSource[] = {
    "MJPegSource\0\0data\0frameReceived(QByteArray*)\0"
    "error()\0start()\0requestFinished()\0"
    "error\0onError(QNetworkReply::NetworkError)\0"
    "sourceHung()\0mjpegDataRead()\0"
};

void MJPegSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MJPegSource *_t = static_cast<MJPegSource *>(_o);
        switch (_id) {
        case 0: _t->frameReceived((*reinterpret_cast< QByteArray*(*)>(_a[1]))); break;
        case 1: _t->error(); break;
        case 2: _t->start(); break;
        case 3: _t->requestFinished(); break;
        case 4: _t->onError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 5: _t->sourceHung(); break;
        case 6: _t->mjpegDataRead(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MJPegSource::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MJPegSource::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MJPegSource,
      qt_meta_data_MJPegSource, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MJPegSource::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MJPegSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MJPegSource::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MJPegSource))
        return static_cast<void*>(const_cast< MJPegSource*>(this));
    return QObject::qt_metacast(_clname);
}

int MJPegSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MJPegSource::frameReceived(QByteArray * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MJPegSource::error()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
