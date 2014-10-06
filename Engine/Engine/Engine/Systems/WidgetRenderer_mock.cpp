/****************************************************************************
** Meta object code from reading C++ file 'WidgetRenderer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "WidgetRenderer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WidgetRenderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetRenderer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WidgetRenderer[] = {
    "WidgetRenderer\0\0nxtFrm()\0"
};

void WidgetRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetRenderer *_t = static_cast<WidgetRenderer *>(_o);
        switch (_id) {
        case 0: _t->nxtFrm(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WidgetRenderer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetRenderer::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_WidgetRenderer,
      qt_meta_data_WidgetRenderer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetRenderer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetRenderer))
        return static_cast<void*>(const_cast< WidgetRenderer*>(this));
    if (!strcmp(_clname, "Renderer"))
        return static_cast< Renderer*>(const_cast< WidgetRenderer*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int WidgetRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
