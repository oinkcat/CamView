/****************************************************************************
** Meta object code from reading C++ file 'apptoolbar.h'
**
** Created: Sun 3. Apr 23:07:30 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../apptoolbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apptoolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AppToolBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      27,   11,   11,   11, 0x05,
      45,   11,   11,   11, 0x05,
      61,   11,   11,   11, 0x05,
      87,   79,   11,   11, 0x05,
     115,  106,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     134,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AppToolBar[] = {
    "AppToolBar\0\0closeClicked()\0minimizeClicked()\0"
    "playerClicked()\0settingsClicked()\0"
    "checked\0audioClicked(bool)\0newValue\0"
    "volumeChanged(int)\0checkTime()\0"
};

void AppToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AppToolBar *_t = static_cast<AppToolBar *>(_o);
        switch (_id) {
        case 0: _t->closeClicked(); break;
        case 1: _t->minimizeClicked(); break;
        case 2: _t->playerClicked(); break;
        case 3: _t->settingsClicked(); break;
        case 4: _t->audioClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->volumeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->checkTime(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AppToolBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AppToolBar::staticMetaObject = {
    { &QToolBar::staticMetaObject, qt_meta_stringdata_AppToolBar,
      qt_meta_data_AppToolBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AppToolBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AppToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AppToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AppToolBar))
        return static_cast<void*>(const_cast< AppToolBar*>(this));
    return QToolBar::qt_metacast(_clname);
}

int AppToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
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
void AppToolBar::closeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void AppToolBar::minimizeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void AppToolBar::playerClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void AppToolBar::settingsClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void AppToolBar::audioClicked(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AppToolBar::volumeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
