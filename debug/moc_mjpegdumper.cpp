/****************************************************************************
** Meta object code from reading C++ file 'mjpegdumper.h'
**
** Created: Sun 3. Apr 23:07:26 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mjpegdumper.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mjpegdumper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MJpegDumper[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      25,   12,   12,   12, 0x0a,
      45,   35,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MJpegDumper[] = {
    "MJpegDumper\0\0beginDump()\0endDump()\0"
    "frameData\0dumpFrameData(QByteArray*)\0"
};

void MJpegDumper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MJpegDumper *_t = static_cast<MJpegDumper *>(_o);
        switch (_id) {
        case 0: _t->beginDump(); break;
        case 1: _t->endDump(); break;
        case 2: _t->dumpFrameData((*reinterpret_cast< QByteArray*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MJpegDumper::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MJpegDumper::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MJpegDumper,
      qt_meta_data_MJpegDumper, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MJpegDumper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MJpegDumper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MJpegDumper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MJpegDumper))
        return static_cast<void*>(const_cast< MJpegDumper*>(this));
    return QThread::qt_metacast(_clname);
}

int MJpegDumper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
