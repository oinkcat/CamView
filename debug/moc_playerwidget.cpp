/****************************************************************************
** Meta object code from reading C++ file 'playerwidget.h'
**
** Created: Sun 3. Apr 23:18:49 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playerwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayerWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   14,   13,   13, 0x05,
      52,   44,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      78,   13,   13,   13, 0x0a,
      91,   85,   13,   13, 0x0a,
     111,  101,   13,   13, 0x0a,
     127,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlayerWidget[] = {
    "PlayerWidget\0\0position\0positionChanged(int)\0"
    "playing\0playingStateChanged(bool)\0"
    "play()\0mtime\0seek(int)\0direction\0"
    "singleStep(int)\0doTimer()\0"
};

void PlayerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayerWidget *_t = static_cast<PlayerWidget *>(_o);
        switch (_id) {
        case 0: _t->positionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->playingStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->play(); break;
        case 3: _t->seek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->singleStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->doTimer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlayerWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlayerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayerWidget,
      qt_meta_data_PlayerWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerWidget))
        return static_cast<void*>(const_cast< PlayerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PlayerWidget::positionChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayerWidget::playingStateChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
