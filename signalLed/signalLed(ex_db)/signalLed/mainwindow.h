#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
/*---port--*/
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QSqlTableModel>
#include<QPainter>

namespace Ui {
class MainWindow;
}

class QSqlTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_go_clicked();
    //检测通讯端口槽函数
    void btn_serial_check(bool);
    //打开选择端口槽函数
    void btn_open_port(bool);
    //关闭选择端口槽函数
    void btn_close_port(bool);
    //接收数据槽函数
    void receive_data();

    void add_data(QString operation, QString inStation_led, QString pos_led);

    int add_datebase(int cmd, QString section,QString inStation_led, QString pos_led);

    void on_btn_delete_clicked();

//    void paintEvent(QPaintEvent *event);

    void on_pushButton_clicked();

    void Sleep(int msec);

private:
    Ui::MainWindow *ui;
    QSqlTableModel*  model;
    //串口全局类声明
    QSerialPort global_port;
    //用户系统初始化
    void setLED(QLabel* label, int color, int size);
    void setRail(QLabel* label, int color,int width, int height);
    void system_init();
    void led_init();
    void signalLED(int cmd);
};

#endif // MAINWINDOW_H
