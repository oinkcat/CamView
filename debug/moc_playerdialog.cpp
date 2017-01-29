/****************************************************************************
** Meta object code from reading C++ file 'playerdialog.h'
**
** Created: Sun 3. Apr 23:18:48 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playerdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayerDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      35,   13,   13,   13, 0x08,
      61,   53,   13,   13, 0x0a,
      90,   82,   13,   13, 0x0a,
     124,  119,   13,   13, 0x0a,
     154,  149,   13,   13, 0x0a,
     180,  174,   13,   13, 0x0a,
     196,   13,   13,   13, 0x0a,
     211,   13,   13,   13, 0x0a,
     233,   13,   13,   13, 0x0a,
     248,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PlayerDialog[] = {
    "PlayerDialog\0\0conversionProgress()\0"
    "recordConverted()\0playing\0"
    "controlPlaying(bool)\0camName\0"
    "populateRecordDates(QString)\0date\0"
    "populateRecords(QString)\0time\0"
    "loadRecord(QString)\0mtime\0seekByTime(int)\0"
    "doSingleStep()\0moveToAnotherRecord()\0"
    "setClipRange()\0saveClip()\0"
};

void PlayerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayerDialog *_t = static_cast<PlayerDialog *>(_o);
        switch (_id) {
        case 0: _t->conversionProgress(); break;
        case 1: _t->recordConverted(); break;
        case 2: _t->controlPlaying((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->populateRecordDates((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->populateRecords((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->loadRecord((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->seekByTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->doSingleStep(); break;
        case 8: _t->moveToAnotherRecord(); break;
        case 9: _t->setClipRange(); break;
        case 10: _t->saveClip(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlayerDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlayerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PlayerDialog,
      qt_meta_data_PlayerDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerDialog))
        return static_cast<void*>(const_cast< PlayerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PlayerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
