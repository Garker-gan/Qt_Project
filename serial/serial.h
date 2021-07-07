#ifndef SERIAL_H
#define SERIAL_H

#include <QMainWindow>

/*-------------user-------------------*/
/*---port--*/
#include <QSerialPort>
#include <QSerialPortInfo>
/*---QString--*/
#include <QString>
/*---QDateTime--*/
#include <QDateTime>
/*---QTimer--*/
#include <QTimer>
/**/
#include <QFile>
#include <QFileDialog>
/**/
#include <QToolBar>
/*---QDebug--*/
#include <QDebug>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"
/* -----------------------------------*/

QT_BEGIN_NAMESPACE
namespace Ui { class Serial; }
QT_END_NAMESPACE

class QSqlTableModel;

class Serial : public QMainWindow
{
    Q_OBJECT

public:
    Serial(QWidget *parent = nullptr);
    ~Serial();

signals:    //自定义信号
    //发送使能信号
    void my_send_signals(bool);

private slots:  //自定义槽函数
    //检测通讯端口槽函数
    void btn_serial_check(bool);
    //打开选择端口槽函数
    void btn_open_port(bool);
    //关闭选择端口槽函数
    void btn_close_port(bool);
    //发送数据槽函数
//    void btn_send_data(bool);

    //接收数据槽函数
    void receive_data(void);
    //清空接收槽函数
    void btn_clear_rev(bool);

    //自动发送复选框槽函数
    void on_checkBox_stateChanged(int arg1);

    //打开发送文件槽函数
    void btn_open_send_file(bool);
    //保存接收日志槽函数
    void btn_save_rev_log(bool);

    void on_btn_start_clicked();

    void on_btn_submit_clicked();

    void on_btn_undo_clicked();

    void on_btn_add_clicked();

    void on_btn_delete_clicked();

    void on_btn_ascend_clicked();

    void on_btn_descend_clicked();

    void on_btn_query_clicked();

    void on_btn_show_clicked();
    void add_name(QString name,QString date);
    void add_temp(float temp);
    void add_data(QString name,float temp,QString date);

    void on_pushButton_clicked();

private:
    Ui::Serial *ui;
    /*--------funtion---------------------*/
    //用户系统初始化
    void system_init();
    //字符串转16进制
    QByteArray QString2Hex(QString str);
    //字符转16进制
    char ConvertHexChar(char ch);
    //16进制转字符
    char ConvertCharHex(char ch);

    QByteArray QHex2String(QString str);
    /*--------variable--------------------*/
    //串口全局类声明
    QSerialPort global_port;
    //自动发送定时器声明
    QTimer *timer;

    QSqlTableModel*  model;
};
#endif // SERIAL_H
