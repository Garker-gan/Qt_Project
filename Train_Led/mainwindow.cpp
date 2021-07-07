#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include "connection.h"
#include<QDateTime>
#include <QPushButton>
#include <QToolBar>
#include <QPainter>
#include<QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("tb1");
    model->select();
    //设置编辑策略OnFieldChange:所有对模型的改变都会立即应用到数据库；OnRowChange:对一条记录的改变会在用户选择另一条记录时被应用；
    //OnManualSubmit所有改变都会在模型中进行缓存，知道调用submitAll()或revertAll()
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);

    system_init();
    led_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::add_data(QString section)
{
    //获得表的行数
    int rowNum = model->rowCount();
    int id = rowNum+1;

    //获取当前系统时间
    QDateTime nowtime = QDateTime::currentDateTime();
    //时间转换为字符串格式
    QString time = nowtime.toString("yyyy-MM-dd hh:mm:ss");
    //添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),id);
    model->setData(model->index(rowNum,1),section);
    model->setData(model->index(rowNum,2),time);
    //可以直接提交
    model->submitAll();
}


// 该函数将label控件变成一个圆形指示灯，需要指定颜色color以及直径size
// color 0:grey 1:red 2:green 3:yellow
// size  单位是像素
void MainWindow::setLED(QLabel* label, int color, int size)
{
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    case 4:
        // 黄色
        background += "rgb(0,0,255)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}


/*---------------------------------------------------------------------
 *             funtion
 * --------------------------------------------------------------------*/
//用户系统初始化
void MainWindow::system_init()
{


    QToolBar *toolBar = addToolBar("toolBar");
    QPushButton *btn_check = new QPushButton("检测串口",this);
    QPushButton *btn_open = new QPushButton("打开串口",this);
    QPushButton *btn_close = new QPushButton("关闭串口",this);

    toolBar->addWidget(btn_check);
    toolBar->addWidget(btn_open);
    toolBar->addWidget(btn_close);

    //connect
    //check port 检测通讯端口
    connect(btn_check,&QPushButton::clicked,this,&MainWindow::btn_serial_check);
    //open port 打开选择端口
    connect(btn_open,&QPushButton::clicked,this,&MainWindow::btn_open_port);
    //close port 关闭选择端口
    connect(btn_close,&QPushButton::clicked,this,&MainWindow::btn_close_port);




//    receive data 串口数据接收完触发更新添加显示接收文本框
    connect(&global_port,&QSerialPort::readyRead,this,&MainWindow::receive_data);
}



/**************************************************************串口通信部分*************************************************************************/
//检测通讯端口槽函数
void MainWindow::btn_serial_check(bool)
{
    ui->cmd_port_name->clear();
    //通过QSerialPortInfo查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cmd_port_name->addItem(info.portName());
    }
}

//打开选择端口槽函数
void MainWindow::btn_open_port(bool)
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
        ui->statusbar->showMessage(status);
        ui->statusbar->setStyleSheet("color:green");
    }
}

//关闭选择端口槽函数
void MainWindow::btn_close_port(bool)
{

    global_port.close();

    //关闭端口后显示状态
    ui->lab_status->setText("CLOSED");
    ui->lab_status->setStyleSheet("color:red");

    //statusBar 状态栏显示端口状态
    QString sm = "%1 CLOSED";
    QString status = sm.arg(global_port.portName());
    ui->statusbar->showMessage(status);
    ui->statusbar->setStyleSheet("color:red");
}

void MainWindow::receive_data(void)
{
    QByteArray array = global_port.readAll();

    QString str_rev;

    //获取当前系统时间
    QDateTime nowtime = QDateTime::currentDateTime();
    //时间转换为字符串格式
    str_rev = "[" + nowtime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
    //加上接收数据 转换为16进制并空格分开 接收数据换行
    str_rev = QString(array.toUpper().append(' ')).append("\r\n");
    char c = str_rev[0].toLatin1();
    int cmd = c - '0';
//    int cmd = str_rev.toInt();

    signalLED(cmd);

    //将光标定位到最后
//    ui->tb_rev->moveCursor(QTextCursor::End);
//    //文本框显示接收数据
//    ui->tb_rev->insertPlainText(str_rev);


}
/**************************************************************信号灯控制部分*************************************************************************/
//添加列车轨道图片
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //绘图前准备画笔、画刷
    QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
    pen.setColor(Qt::black);
    pen.setWidth(5);
    QPainter painter(this);   //可在QPaintDevice上绘制各种图形。QPaintDevice有之类QWidget、QImage、QOpenGLPaintDevice等
    painter.setPen(pen);
    painter.drawLine(QPoint(50,250),QPoint(this->rect().width()-50,250));   //QPainter绘制直线
    painter.drawLine(QPoint(50,350),QPoint(this->rect().width()-50,350));
    painter.drawLine(QPoint(100,250),QPoint(100,350));
    painter.drawLine(QPoint(200,250),QPoint(200,350));
    painter.drawLine(QPoint(300,250),QPoint(300,350));
    painter.drawLine(QPoint(400,250),QPoint(400,350));
    painter.drawLine(QPoint(500,250),QPoint(500,350));
    painter.drawLine(QPoint(600,250),QPoint(600,350));
    painter.drawLine(QPoint(700,250),QPoint(700,350));
}



void MainWindow::led_init()
{
    setLED(ui->red1, 0, 32);
    setLED(ui->green1, 2, 32);
    setLED(ui->yellow1, 0, 32);

    setLED(ui->red1_2, 0, 32);
    setLED(ui->green1_2, 2, 32);
    setLED(ui->yellow1_2, 0, 32);

    setLED(ui->red1_3, 0, 32);
    setLED(ui->green1_3, 2, 32);
    setLED(ui->yellow1_3, 0, 32);

    setLED(ui->red1_4, 0, 32);
    setLED(ui->green1_4, 2, 32);
    setLED(ui->yellow1_4, 0, 32);

    setLED(ui->red1_5, 0, 32);
    setLED(ui->green1_5, 2, 32);
    setLED(ui->yellow1_5, 0, 32);

    setLED(ui->red1_6, 0, 32);
    setLED(ui->green1_6, 2, 32);
    setLED(ui->yellow1_6, 0, 32);

    setLED(ui->rail001, 0, 32);
    setLED(ui->rail002, 0, 32);
    setLED(ui->rail003, 0, 32);
    setLED(ui->rail004, 0, 32);
    setLED(ui->rail005, 0, 32);
    setLED(ui->rail006, 0, 32);
}

//根据列车所在区间做出相应的信号灯变化
// 0 grey 1 red 2 green 3 yellow 4 blue
void MainWindow::signalLED(int cmd)
{
    switch (cmd) {
        //列车在区间001
        case 1:
        {
            setLED(ui->red1, 1, 32);
            setLED(ui->green1, 0, 32);
            setLED(ui->yellow1, 0, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 2, 32);
            setLED(ui->yellow1_2, 0, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 2, 32);
            setLED(ui->yellow1_3, 0, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 2, 32);
            setLED(ui->yellow1_4, 0, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 2, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 4, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 0, 32);

            //添加到数据库
            add_datebase(1, "001");
            break;
        }
        case 2:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 0, 32);
            setLED(ui->yellow1, 3, 32);

            setLED(ui->red1_2, 1, 32);
            setLED(ui->green1_2, 0, 32);
            setLED(ui->yellow1_2, 0, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 2, 32);
            setLED(ui->yellow1_3, 0, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 2, 32);
            setLED(ui->yellow1_4, 0, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 2, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 4, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 0, 32);

            //添加到数据库
            add_datebase(2, "002");
            break;
        }

        case 3:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 2, 32);
            setLED(ui->yellow1, 3, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 0, 32);
            setLED(ui->yellow1_2, 3, 32);

            setLED(ui->red1_3, 1, 32);
            setLED(ui->green1_3, 0, 32);
            setLED(ui->yellow1_3, 0, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 2, 32);
            setLED(ui->yellow1_4, 0, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 2, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 4, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 0, 32);

            //添加到数据库
            add_datebase(3, "003");
            break;
        }
        case 4:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 2, 32);
            setLED(ui->yellow1, 0, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 2, 32);
            setLED(ui->yellow1_2, 3, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 0, 32);
            setLED(ui->yellow1_3, 3, 32);

            setLED(ui->red1_4, 1, 32);
            setLED(ui->green1_4, 0, 32);
            setLED(ui->yellow1_4, 0, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 2, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 4, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 0, 32);

            //添加到数据库
            add_datebase(4, "004");
            break;
        }
        case 5:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 2, 32);
            setLED(ui->yellow1, 0, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 2, 32);
            setLED(ui->yellow1_2, 0, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 2, 32);
            setLED(ui->yellow1_3, 3, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 0, 32);
            setLED(ui->yellow1_4, 3, 32);

            setLED(ui->red1_5, 1, 32);
            setLED(ui->green1_5, 0, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);


            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 4, 32);
            setLED(ui->rail006, 0, 32);

            //添加到数据库
            add_datebase(5, "005");
            break;
        }
        case 6:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 2, 32);
            setLED(ui->yellow1, 0, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 2, 32);
            setLED(ui->yellow1_2, 0, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 2, 32);
            setLED(ui->yellow1_3, 0, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 2, 32);
            setLED(ui->yellow1_4, 3, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 0, 32);
            setLED(ui->yellow1_5, 3, 32);

            setLED(ui->red1_6, 1, 32);
            setLED(ui->green1_6, 0, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 4, 32);

            //添加到数据库
            add_datebase(6, "006");
            break;
        }
        default:
        {
            led_init();
            break;
        }
    }

}

int pre_cmd;
int MainWindow::add_datebase(int cmd, QString section)
{
    if(pre_cmd == cmd)
        return 0;
    else
    {
        add_data(section);
        pre_cmd = cmd;
        return 1;

    }
}

void MainWindow::on_go_clicked()
{
//    int count = qrand()%7;
//    signalLED(count);
    led_init();
}

void MainWindow::on_btn_delete_clicked()
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




//按键演示
void MainWindow::buttonShow(int cmd)
{
    switch (cmd) {
        //列车在区间001
        case 1:
        {
            setLED(ui->red1, 1, 32);
            setLED(ui->green1, 0, 32);
            setLED(ui->yellow1, 0, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 2, 32);
            setLED(ui->yellow1_2, 0, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 2, 32);
            setLED(ui->yellow1_3, 0, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 2, 32);
            setLED(ui->yellow1_4, 0, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 2, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 4, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 0, 32);

            break;
        }
        case 2:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 0, 32);
            setLED(ui->yellow1, 3, 32);

            setLED(ui->red1_2, 1, 32);
            setLED(ui->green1_2, 0, 32);
            setLED(ui->yellow1_2, 0, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 2, 32);
            setLED(ui->yellow1_3, 0, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 2, 32);
            setLED(ui->yellow1_4, 0, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 2, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 4, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 0, 32);

            break;
        }

        case 3:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 2, 32);
            setLED(ui->yellow1, 3, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 0, 32);
            setLED(ui->yellow1_2, 3, 32);

            setLED(ui->red1_3, 1, 32);
            setLED(ui->green1_3, 0, 32);
            setLED(ui->yellow1_3, 0, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 2, 32);
            setLED(ui->yellow1_4, 0, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 2, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 4, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 0, 32);

            break;
        }
        case 4:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 2, 32);
            setLED(ui->yellow1, 0, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 2, 32);
            setLED(ui->yellow1_2, 3, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 0, 32);
            setLED(ui->yellow1_3, 3, 32);

            setLED(ui->red1_4, 1, 32);
            setLED(ui->green1_4, 0, 32);
            setLED(ui->yellow1_4, 0, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 2, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 4, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 0, 32);

            break;
        }
        case 5:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 2, 32);
            setLED(ui->yellow1, 0, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 2, 32);
            setLED(ui->yellow1_2, 0, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 2, 32);
            setLED(ui->yellow1_3, 3, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 0, 32);
            setLED(ui->yellow1_4, 3, 32);

            setLED(ui->red1_5, 1, 32);
            setLED(ui->green1_5, 0, 32);
            setLED(ui->yellow1_5, 0, 32);

            setLED(ui->red1_6, 0, 32);
            setLED(ui->green1_6, 2, 32);
            setLED(ui->yellow1_6, 0, 32);


            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 4, 32);
            setLED(ui->rail006, 0, 32);

            break;
        }
        case 6:
        {
            setLED(ui->red1, 0, 32);
            setLED(ui->green1, 2, 32);
            setLED(ui->yellow1, 0, 32);

            setLED(ui->red1_2, 0, 32);
            setLED(ui->green1_2, 2, 32);
            setLED(ui->yellow1_2, 0, 32);

            setLED(ui->red1_3, 0, 32);
            setLED(ui->green1_3, 2, 32);
            setLED(ui->yellow1_3, 0, 32);

            setLED(ui->red1_4, 0, 32);
            setLED(ui->green1_4, 2, 32);
            setLED(ui->yellow1_4, 3, 32);

            setLED(ui->red1_5, 0, 32);
            setLED(ui->green1_5, 0, 32);
            setLED(ui->yellow1_5, 3, 32);

            setLED(ui->red1_6, 1, 32);
            setLED(ui->green1_6, 0, 32);
            setLED(ui->yellow1_6, 0, 32);

            setLED(ui->rail001, 0, 32);
            setLED(ui->rail002, 0, 32);
            setLED(ui->rail003, 0, 32);
            setLED(ui->rail004, 0, 32);
            setLED(ui->rail005, 0, 32);
            setLED(ui->rail006, 4, 32);

            break;
        }
        default:
        {
            led_init();
            break;
        }
    }

}


void MainWindow::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


//根据输入的列车区间进行演示
void MainWindow::on_pushButton_clicked()
{
    int cmd = ui->textEdit->toPlainText().toInt();
    while(cmd<=6)
    {
        buttonShow(cmd);
        Sleep(1000);
        cmd++;
    }
    led_init();
}
