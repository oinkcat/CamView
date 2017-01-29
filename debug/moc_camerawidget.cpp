/****************************************************************************
** Meta object code from reading C++ file 'camerawidget.h'
**
** Created: Sun 3. Apr 23:18:47 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../camerawidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camerawidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CameraWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      30,   13,   13,   13, 0x05,
      50,   13,   13,   13, 0x05,
      74,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,   92,   13,   13, 0x08,
     130,  122,   13,   13, 0x08,
     148,   13,   13,   13, 0x08,
     165,   13,   13,   13, 0x08,
     180,   13,   13,   13, 0x08,
     198,  196,   13,   13, 0x08,
     222,   13,   13,   13, 0x08,
     242,   13,   13,   13, 0x0a,
     269,  258,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CameraWidget[] = {
    "CameraWidget\0\0doubleClicked()\0"
    "settingsRequested()\0deleteCameraRequested()\0"
    "repairRequested()\0data\0imageLoaded(QByteArray*)\0"
    "percent\0updateMotion(int)\0startRecording()\0"
    "sourceFailed()\0controlRecord()\0p\0"
    "showContextMenu(QPoint)\0clearRepairStatus()\0"
    "stopRecording()\0statusCode\0"
    "showRepairStatus(int)\0"
};

void CameraWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CameraWidget *_t = static_cast<CameraWidget *>(_o);
        switch (_id) {
        case 0: _t->doubleClicked(); break;
        case 1: _t->settingsRequested(); break;
        case 2: _t->deleteCameraRequested(); break;
        case 3: _t->repairRequested(); break;
        case 4: _t->imageLoaded((*reinterpret_cast< QByteArray*(*)>(_a[1]))); break;
        case 5: _t->updateMotion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->startRecording(); break;
        case 7: _t->sourceFailed(); break;
        case 8: _t->controlRecord(); break;
        case 9: _t->showContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 10: _t->clearRepairStatus(); break;
        case 11: _t->stopRecording(); break;
        case 12: _t->showRepairStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CameraWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CameraWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CameraWidget,
      qt_meta_data_CameraWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CameraWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CameraWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CameraWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CameraWidget))
        return static_cast<void*>(const_cast< CameraWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CameraWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CameraWidget::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CameraWidget::settingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CameraWidget::deleteCameraRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CameraWidget::repairRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
