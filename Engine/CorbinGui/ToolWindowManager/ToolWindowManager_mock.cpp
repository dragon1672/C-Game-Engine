/****************************************************************************
** Meta object code from reading C++ file 'ToolWindowManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ToolWindowManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToolWindowManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ToolWindowManager_t {
    QByteArrayData data[12];
    char stringdata[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ToolWindowManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ToolWindowManager_t qt_meta_stringdata_ToolWindowManager = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 27),
QT_MOC_LITERAL(2, 46, 0),
QT_MOC_LITERAL(3, 47, 8),
QT_MOC_LITERAL(4, 56, 10),
QT_MOC_LITERAL(5, 67, 7),
QT_MOC_LITERAL(6, 75, 22),
QT_MOC_LITERAL(7, 98, 17),
QT_MOC_LITERAL(8, 116, 5),
QT_MOC_LITERAL(9, 122, 24),
QT_MOC_LITERAL(10, 147, 17),
QT_MOC_LITERAL(11, 165, 19)
    },
    "ToolWindowManager\0toolWindowVisibilityChanged\0"
    "\0QWidget*\0toolWindow\0visible\0"
    "showNextDropSuggestion\0tabCloseRequested\0"
    "index\0suggestionSwitchInterval\0"
    "borderSensitivity\0rubberBandLineWidth"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToolWindowManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   34,    2, 0x08 /* Private */,
       7,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

 // properties: name, type, flags
       9, QMetaType::Int, 0x00095103,
      10, QMetaType::Int, 0x00095103,
      11, QMetaType::Int, 0x00095103,

       0        // eod
};

void ToolWindowManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ToolWindowManager *_t = static_cast<ToolWindowManager *>(_o);
        switch (_id) {
        case 0: _t->toolWindowVisibilityChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->showNextDropSuggestion(); break;
        case 2: _t->tabCloseRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ToolWindowManager::*_t)(QWidget * , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ToolWindowManager::toolWindowVisibilityChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ToolWindowManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ToolWindowManager.data,
      qt_meta_data_ToolWindowManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *ToolWindowManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToolWindowManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolWindowManager.stringdata))
        return static_cast<void*>(const_cast< ToolWindowManager*>(this));
    return QWidget::qt_metacast(_clname);
}

int ToolWindowManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = suggestionSwitchInterval(); break;
        case 1: *reinterpret_cast< int*>(_v) = borderSensitivity(); break;
        case 2: *reinterpret_cast< int*>(_v) = rubberBandLineWidth(); break;
        default: break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSuggestionSwitchInterval(*reinterpret_cast< int*>(_v)); break;
        case 1: setBorderSensitivity(*reinterpret_cast< int*>(_v)); break;
        case 2: setRubberBandLineWidth(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ToolWindowManager::toolWindowVisibilityChanged(QWidget * _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
