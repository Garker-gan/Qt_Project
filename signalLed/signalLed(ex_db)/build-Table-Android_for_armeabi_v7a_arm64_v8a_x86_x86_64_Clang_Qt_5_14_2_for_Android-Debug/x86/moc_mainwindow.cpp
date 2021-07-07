/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../signalLed/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "on_go_clicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "btn_serial_check"
QT_MOC_LITERAL(4, 43, 13), // "btn_open_port"
QT_MOC_LITERAL(5, 57, 14), // "btn_close_port"
QT_MOC_LITERAL(6, 72, 12), // "receive_data"
QT_MOC_LITERAL(7, 85, 8), // "add_data"
QT_MOC_LITERAL(8, 94, 9), // "operation"
QT_MOC_LITERAL(9, 104, 13), // "inStation_led"
QT_MOC_LITERAL(10, 118, 7), // "pos_led"
QT_MOC_LITERAL(11, 126, 12), // "add_datebase"
QT_MOC_LITERAL(12, 139, 3), // "cmd"
QT_MOC_LITERAL(13, 143, 7), // "section"
QT_MOC_LITERAL(14, 151, 21), // "on_btn_delete_clicked"
QT_MOC_LITERAL(15, 173, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(16, 195, 5), // "Sleep"
QT_MOC_LITERAL(17, 201, 4) // "msec"

    },
    "MainWindow\0on_go_clicked\0\0btn_serial_check\0"
    "btn_open_port\0btn_close_port\0receive_data\0"
    "add_data\0operation\0inStation_led\0"
    "pos_led\0add_datebase\0cmd\0section\0"
    "on_btn_delete_clicked\0on_pushButton_clicked\0"
    "Sleep\0msec"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    1,   65,    2, 0x08 /* Private */,
       4,    1,   68,    2, 0x08 /* Private */,
       5,    1,   71,    2, 0x08 /* Private */,
       6,    0,   74,    2, 0x08 /* Private */,
       7,    3,   75,    2, 0x08 /* Private */,
      11,    4,   82,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    1,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,   10,
    QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,   12,   13,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_go_clicked(); break;
        case 1: _t->btn_serial_check((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->btn_open_port((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->btn_close_port((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->receive_data(); break;
        case 5: _t->add_data((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: { int _r = _t->add_datebase((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->on_btn_delete_clicked(); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->Sleep((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
