/****************************************************************************
** Meta object code from reading C++ file 'layermanagerdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../layermanagerdialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layermanagerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSLayerManagerDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSLayerManagerDialogENDCLASS = QtMocHelpers::stringData(
    "LayerManagerDialog",
    "addLayer",
    "",
    "deleteLayer",
    "clearLayer",
    "toggleVisibility",
    "renameLayer",
    "currentLayerChanged",
    "row",
    "updateLayerList",
    "updateLayerOpacity",
    "value",
    "moveLayerUp",
    "moveLayerDown"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLayerManagerDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    0,   75,    2, 0x08,    2 /* Private */,
       4,    0,   76,    2, 0x08,    3 /* Private */,
       5,    0,   77,    2, 0x08,    4 /* Private */,
       6,    0,   78,    2, 0x08,    5 /* Private */,
       7,    1,   79,    2, 0x08,    6 /* Private */,
       9,    0,   82,    2, 0x08,    8 /* Private */,
      10,    1,   83,    2, 0x08,    9 /* Private */,
      12,    0,   86,    2, 0x08,   11 /* Private */,
      13,    0,   87,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject LayerManagerDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSLayerManagerDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLayerManagerDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLayerManagerDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LayerManagerDialog, std::true_type>,
        // method 'addLayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteLayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearLayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'renameLayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentLayerChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateLayerList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateLayerOpacity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'moveLayerUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moveLayerDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void LayerManagerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LayerManagerDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addLayer(); break;
        case 1: _t->deleteLayer(); break;
        case 2: _t->clearLayer(); break;
        case 3: _t->toggleVisibility(); break;
        case 4: _t->renameLayer(); break;
        case 5: _t->currentLayerChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->updateLayerList(); break;
        case 7: _t->updateLayerOpacity((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->moveLayerUp(); break;
        case 9: _t->moveLayerDown(); break;
        default: ;
        }
    }
}

const QMetaObject *LayerManagerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LayerManagerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLayerManagerDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int LayerManagerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
