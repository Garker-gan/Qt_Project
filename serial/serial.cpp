#include "serial.h"
#include "ui_serial.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include "connection.h"
#include<QApplication>


Serial::Serial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Serial)
{
    ui->setupUi(this);
    /*----------user-----------*/
    //init 用户系统初始化
    model = new QSqlTableModel(this);
    model->setTable("s2");
    model->select();
    //设置编辑策略OnFieldChange:所有对模型的改变都会立即应用到数据库；OnRowChange:对一条记录的改变会在用户选择另一条记录时被应用；
    //OnManualSubmit所有改变都会在模型中进行缓存，知道调用submitAll()或revertAll()
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView->setModel(model);

    system_init();
}

Serial::~Serial()
{
    delete ui;
}

/*---------------------------------------------------------------------
 *             funtion
 * --------------------------------------------------------------------*/
//用户系统初始化
void Serial::system_init()
{
    //port conifg
    ui->cmd_port_name->clear();
    //通过QSerialPortInfo查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        //将可用串口添加到端口显示框
        ui->cmd_port_name->addItem(info.portName());
    }

    //设置串口状态标签为红色 表示未连接状态
//    ui->lab_status->setStyleSheet("color:red");
    //statusBar 状态栏显示端口状态 未连接
    QString sm = "%1 CLOSED";
    QString status = sm.arg(ui->cmd_port_name->currentText());
    ui->statusBar->showMessage(status);
    ui->statusBar->setStyleSheet("color:red");

    //timer 自动发送
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        emit my_send_signals(true); //触发发送信号
    });

    QToolBar *toolBar = addToolBar("toolBar");
    QPushButton *btn_check = new QPushButton("检测串口",this);
    QPushButton *btn_open = new QPushButton("打开串口",this);
    QPushButton *btn_close = new QPushButton("关闭串口",this);
    QPushButton *btn_clear = new QPushButton("清空接收",this);
    QPushButton *btn_file = new QPushButton("打开文件",this);
    QPushButton *btn_log = new QPushButton("保存日志",this);
    toolBar->addWidget(btn_check);
    toolBar->addWidget(btn_open);
    toolBar->addWidget(btn_close);
    toolBar->addWidget(btn_clear);
    toolBar->addWidget(btn_file);
    toolBar->addWidget(btn_log);

    //connect
    //check port 检测通讯端口
    connect(btn_check,&QPushButton::clicked,this,&Serial::btn_serial_check);
    //open port 打开选择端口
    connect(btn_open,&QPushButton::clicked,this,&Serial::btn_open_port);
    //close port 关闭选择端口
    connect(btn_close,&QPushButton::clicked,this,&Serial::btn_close_port);
    //clear recevie 清除接收文本框的内容
    connect(btn_clear,&QPushButton::clicked,this,&Serial::btn_clear_rev);
    //打开发送文件
    connect(btn_file,&QPushButton::clicked,this,&Serial::btn_open_send_file);
    //保存接收日志
    connect(btn_log,&QPushButton::clicked,this,&Serial::btn_save_rev_log);

    //send data 发送按钮 触发发送信号
//    connect(ui->btn_send,&QPushButton::clicked,[=](){
//        emit my_send_signals(true);
//    });
    //发送信号   发送槽函数
//    connect(this,&Serial::my_send_signals,this,&Serial::btn_send_data);

    //receive data 串口数据接收完触发更新添加显示接收文本框
    connect(&global_port,&QSerialPort::readyRead,this,&Serial::receive_data);
}

//字符串转16进制
QByteArray Serial::QString2Hex(QString str)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();

    senddata.resize(len/2);
    char lstr,hstr;

    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}
//字符转16进制
char Serial::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}

//字符串转16进制
QByteArray Serial::QHex2String(QString str)
{
    QByteArray G2 = QByteArray::fromHex(QString(str).toUtf8());
    return G2;
}

//16进制转字符
char Serial::ConvertCharHex(char ch)
{
    return ch + 'a' -10;
}

/*---------------------------------------------------------------------
 *             slots
 * --------------------------------------------------------------------*/
//检测通讯端口槽函数
void Serial::btn_serial_check(bool)
{
    ui->cmd_port_name->clear();
    //通过QSerialPortInfo查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cmd_port_name->addItem(info.portName());
    }
}

//打开选择端口槽函数
void Serial::btn_open_port(bool)
{
    //port name 设置端口
    global_port.setPortName(ui->cmd_port_name->currentText());
    //baud rate 设置波特率
    global_port.setBaudRate(9600);
    //parity 设置校验位
    global_port.setParity(QSerialPort::NoParity);


    //data bits 设置数据位
    global_port.setDataBits(QSerialPort::Data8);

    //stop bits 设置停止位
    global_port.setStopBits(QSerialPort::OneStop);


    //port open 打开选择端口
    bool ret = global_port.open(QIODevice::ReadWrite);

    if(ret){
        //打开成功更新状态
        ui->lab_status->setText("OPENED");
        //设置串口状态标签为绿色 表示已连接状态
        ui->lab_status->setStyleSheet("color:green");

        //statusBar 状态栏显示端口状态
        QString sm = "%1 OPENED, %2, 8, NONE, 1";
        QString status = sm.arg(global_port.portName()).arg(global_port.baudRate());
        ui->statusBar->showMessage(status);
        ui->statusBar->setStyleSheet("color:green");
    }
}

//关闭选择端口槽函数
void Serial::btn_close_port(bool)
{

    global_port.close();

    //关闭端口后显示状态
    ui->lab_status->setText("CLOSED");
    ui->lab_status->setStyleSheet("color:red");

    //statusBar 状态栏显示端口状态
    QString sm = "%1 CLOSED";
    QString status = sm.arg(global_port.portName());
    ui->statusBar->showMessage(status);
    ui->statusBar->setStyleSheet("color:red");
}

//发送数据槽函数
//void Serial::btn_send_data(bool)
//{
//    QString data = ui->nameEdit->toPlainText();
//    QByteArray array;

//    //Hex复选框
////    if(ui->chk_send_hex->checkState() == Qt::Checked){
//    array = QString2Hex(data);  //HEX 16进制
////    }else{
////        array = data.toLatin1();    //ASCII
////    }
//    global_port.write(array);   //发送数据
//}


int count = 0;
//接收数据槽函数
void Serial::receive_data(void)
{
    QByteArray array = global_port.readAll();

    QString str_rev;

    //获取当前系统时间
    QDateTime nowtime = QDateTime::currentDateTime();

    str_rev = QString(array.toUpper().append(' ')).append("\r\n");
//    QString name = QString(array[0]);
//    float temp = on_btn_temp_clicked();
    //添加一行
//    add_name(str_rev,nowtime.toString("yyyyMMdd"));
//    add_temp(36.8);


//    if(ui->chk_rev_hex->checkState() == Qt::Checked){   //HEX 16进制
//        if(ui->chk_rev_line->checkState() == Qt::Checked){  //自动换行
//            if(ui->chk_rev_time->checkState() == Qt::Checked){  //显示时间
//                //获取当前系统时间
//                QDateTime nowtime = QDateTime::currentDateTime();
//                //时间转换为字符串格式
//                str_rev = "[" + nowtime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
//                //加上接收数据 转换为16进制并空格分开 接收数据换行
//                str_rev += QString(array.toHex(' ').toUpper().append(' ')).append("\r\n");
//            }else{
//                str_rev = QString(array.toHex(' ').toUpper().append(' ')).append("\r\n");
//            }
//        }else{
//            str_rev = QString(array.toHex(' ').toUpper().append(' '));
//        }

//    }else{
//        if(ui->chk_rev_line->checkState() == Qt::Checked){
//            if(ui->chk_rev_time->checkState() == Qt::Checked){
//                QDateTime nowtime = QDateTime::currentDateTime();
//                str_rev = "[" + nowtime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
//                str_rev += QString(array).append("\r\n");
//            }else{
//                str_rev = QString(array).append("\r\n");
//            }
//        }else{
//            str_rev = QString(array);
//        }

//    }


    //将光标定位到最后
    ui->tb_rev->moveCursor(QTextCursor::End);
    //文本框显示接收数据
    ui->tb_rev->insertPlainText(str_rev);

    if(str_rev != ' ')
    {
        if(count == 0)
        {
            QByteArray name = QHex2String(str_rev);
            add_name(name,nowtime.toString("yyyyMMdd"));
        }
        if(count == 1)
        {
            add_temp(str_rev.toFloat());
        }
        count++;
        if(count == 2)
            count = 0;

    }


}

//清空接收文本框槽函数
void Serial::btn_clear_rev(bool)
{
    ui->tb_rev->clear();
}

//自动触发复选框  启动定时器和停止定时器
void Serial::on_checkBox_stateChanged(int arg1)
{
//    if(arg1){
//        timer->start(ui->spinBox->value()); //启动定时器
//    }else{
//        timer->stop();  //停止定时器
//    }
}

//打开发送文件槽函数
void Serial::btn_open_send_file(bool)
{
//    QString path = QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
//    if(!path.isEmpty()){
//        QFile file(path);
//        bool isOk = file.open(QIODevice::ReadOnly);
//        if(isOk){
//            ui->pte_send->setPlainText(QString(file.readAll()));
//        }
//        file.close();
//    }
}

//保存接收日志槽函数
void Serial::btn_save_rev_log(bool)
{
    QString path = QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
    if(!path.isEmpty()){
        QFile file(path);
        bool isOk = file.open(QIODevice::WriteOnly);
        if(isOk){
            file.write(ui->tb_rev->toPlainText().toStdString().data());
        }
        file.close();
    }
}

//寻卡
void Serial::on_btn_start_clicked()
{
    QByteArray cmd("1");
    global_port.write(cmd);


}


//提交修改按钮
void Serial::on_btn_submit_clicked()
{
    //开始事务操作
    model->database().transaction();
    if(model->submitAll())
    {
        if(model->database().commit())//提交
        {
           QMessageBox::information(this,tr("tableModel"),tr("数据库修改成功！"));
        }
        else
        {
            model->database().rollback();//回滚
            QMessageBox::warning(this,tr("tableModel"),tr("数据库错误：%1").arg(model->lastError().text()),QMessageBox::Ok);
        }
    }
}

//撤销修改，只能撤销未提交的修改
void Serial::on_btn_undo_clicked()
{
    model->revertAll();
}

//查询按钮，就行筛选
void Serial::on_btn_query_clicked()
{
    QString name = ui->lineEdit->text();
    //根据姓名进行筛选，一定要使用单引号
    model->setFilter(QString("name='%1'").arg(name));
    model->select();
}
//按日期查询
void Serial::on_pushButton_clicked()
{
    QString date = ui->lineEdit->text();
    //根据姓名进行筛选，一定要使用单引号
    model->setFilter(QString("date='%1'").arg(date));
    model->select();
}


//显示全表
void Serial::on_btn_show_clicked()
{
    model->setTable("s2");
    model->select();
}

//按id升序排列
void Serial::on_btn_ascend_clicked()
{
    model->setSort(0,Qt::AscendingOrder);
    model->select();
}
//按id降序排列
void Serial::on_btn_descend_clicked()
{
    model->setSort(0,Qt::DescendingOrder);
    model->select();
}
//删除选中行
void Serial::on_btn_delete_clicked()
{
    //获取选中的行
    int curRow = ui->tableView->currentIndex().row();
    //删除改行
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,QString::fromLocal8Bit("删除当前行"),QString::fromLocal8Bit("你确定删除当前行吗?"),QMessageBox::Yes,QMessageBox::No);
    //QMessageBox::warning(this,tr("删除当前行"),tr("你确定删除当前行吗?"),QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::No)
    {
        model->revertAll();//如果不删除，则撤销
    }
    else
    {
        model->submitAll();//否则提交，在数据库中删除该行
    }
}

//添加记录按钮
void Serial::on_btn_add_clicked()
{
    //获得表的行数
    int rowNum = model->rowCount();
    int id = rowNum+1;
    //添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),id);
    //可以直接提交
    model->submitAll();
}

void Serial::add_name(QString name,QString date)
{
    //获得表的行数
    int rowNum = model->rowCount();
    int id = rowNum+1;
    //添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),id);
    model->setData(model->index(rowNum,1),name);
    model->setData(model->index(rowNum,3),date);

    //可以直接提交
//    model->submitAll();
}

void Serial::add_temp(float temp)
{
    //获得表的行数
    int rowNum = model->rowCount();
    //添加一行
    model->setData(model->index(rowNum-1,2),temp);

    //可以直接提交
    model->submitAll();
    if(temp > 37.5)
    {
        QApplication::beep();
        QMessageBox::information(this,tr("体温异常"),tr("体温超过37.5"));
    }
}

void Serial::add_data(QString name,float temp,QString date)
{
    //获得表的行数
    int rowNum = model->rowCount();
    int id = rowNum+1;
    //添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),id);
    model->setData(model->index(rowNum,1),name);
    model->setData(model->index(rowNum,2),temp);
    model->setData(model->index(rowNum,3),date);

    //可以直接提交
//    model->submitAll();
}




