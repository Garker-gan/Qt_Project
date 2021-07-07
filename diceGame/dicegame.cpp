#include "dicegame.h"
#include "ui_dicegame.h"


diceGame::diceGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::diceGame)
{
    ui->setupUi(this);
    ui->diceNum->setValue(2);
}

diceGame::~diceGame()
{
    delete ui;
}

//3号标签显示
void diceGame::showGif3(int num)
{
    switch (num) {
        case 0:{
            QMovie *movie = new QMovie("../diceGame/1.gif");
            ui->label3->setMovie(movie);
            movie->start();
            break;
        }

        case 1:{
            QMovie *movie = new QMovie("../diceGame/2.gif");
            ui->label3->setMovie(movie);
            movie->start();
            break;
        }

        case 2:{
            QMovie *movie = new QMovie("../diceGame/3.gif");
            ui->label3->setMovie(movie);
            movie->start();
            break;
        }

        case 3:{
            QMovie *movie = new QMovie("../diceGame/4.gif");
            ui->label3->setMovie(movie);
            movie->start();
            break;
        }

        case 4:{
            QMovie *movie = new QMovie("../diceGame/5.gif");
            ui->label3->setMovie(movie);
            movie->start();
            break;
        }

        case 5:{
            QMovie *movie = new QMovie("../diceGame/6.gif");
            ui->label3->setMovie(movie);
            movie->start();
            break;
        }
    }
}

//1号标签显示
void diceGame::showGif1(int num)
{
    switch (num) {
        case 0:{
            QMovie *movie = new QMovie("../diceGame/1.gif");
            ui->label1->setMovie(movie);
            movie->start();
            break;
        }

        case 1:{
            QMovie *movie = new QMovie("../diceGame/2.gif");
            ui->label1->setMovie(movie);
            movie->start();
            break;
        }

        case 2:{
            QMovie *movie = new QMovie("../diceGame/3.gif");
            ui->label1->setMovie(movie);
            movie->start();
            break;
        }

        case 3:{
            QMovie *movie = new QMovie("../diceGame/4.gif");
            ui->label1->setMovie(movie);
            movie->start();
            break;
        }

        case 4:{
            QMovie *movie = new QMovie("../diceGame/5.gif");
            ui->label1->setMovie(movie);
            movie->start();
            break;
        }

        case 5:{
            QMovie *movie = new QMovie("../diceGame/6.gif");
            ui->label1->setMovie(movie);
            movie->start();
            break;
        }
    }
}

//2号标签显示
void diceGame::showGif2(int num)
{
    switch (num) {
        case 0:{
            QMovie *movie = new QMovie("../diceGame/1.gif");
            ui->label2->setMovie(movie);
            movie->start();
            break;
        }

        case 1:{
            QMovie *movie = new QMovie("../diceGame/2.gif");
            ui->label2->setMovie(movie);
            movie->start();
            break;
        }

        case 2:{
            QMovie *movie = new QMovie("../diceGame/3.gif");
            ui->label2->setMovie(movie);
            movie->start();
            break;
        }

        case 3:{
            QMovie *movie = new QMovie("../diceGame/4.gif");
            ui->label2->setMovie(movie);
            movie->start();
            break;
        }

        case 4:{
            QMovie *movie = new QMovie("../diceGame/5.gif");
            ui->label2->setMovie(movie);
            movie->start();
            break;
        }

        case 5:{
            QMovie *movie = new QMovie("../diceGame/6.gif");
            ui->label2->setMovie(movie);
            movie->start();
            break;
        }
    }
}

//4号标签显示
void diceGame::showGif4(int num)
{
    switch (num) {
        case 0:{
            QMovie *movie = new QMovie("../diceGame/1.gif");
            ui->label4->setMovie(movie);
            movie->start();
            break;
        }

        case 1:{
            QMovie *movie = new QMovie("../diceGame/2.gif");
            ui->label4->setMovie(movie);
            movie->start();
            break;
        }

        case 2:{
            QMovie *movie = new QMovie("../diceGame/3.gif");
            ui->label4->setMovie(movie);
            movie->start();
            break;
        }

        case 3:{
            QMovie *movie = new QMovie("../diceGame/4.gif");
            ui->label4->setMovie(movie);
            movie->start();
            break;
        }

        case 4:{
            QMovie *movie = new QMovie("../diceGame/5.gif");
            ui->label4->setMovie(movie);
            movie->start();
            break;
        }

        case 5:{
            QMovie *movie = new QMovie("../diceGame/6.gif");
            ui->label4->setMovie(movie);
            movie->start();
            break;
        }
    }
}

//5号标签显示
void diceGame::showGif5(int num)
{
    switch (num) {
        case 0:{
            QMovie *movie = new QMovie("../diceGame/1.gif");
            ui->label5->setMovie(movie);
            movie->start();
            break;
        }

        case 1:{
            QMovie *movie = new QMovie("../diceGame/2.gif");
            ui->label5->setMovie(movie);
            movie->start();
            break;
        }

        case 2:{
            QMovie *movie = new QMovie("../diceGame/3.gif");
            ui->label5->setMovie(movie);
            movie->start();
            break;
        }

        case 3:{
            QMovie *movie = new QMovie("../diceGame/4.gif");
            ui->label5->setMovie(movie);
            movie->start();
            break;
        }

        case 4:{
            QMovie *movie = new QMovie("../diceGame/5.gif");
            ui->label5->setMovie(movie);
            movie->start();
            break;
        }

        case 5:{
            QMovie *movie = new QMovie("../diceGame/6.gif");
            ui->label5->setMovie(movie);
            movie->start();
            break;
        }
    }
}



//按键开始
void diceGame::on_start_clicked()
{
    clearLabel();
    int num1,num2,num3,num4,num5;
    //获取骰子数目
    int dice_num = ui->diceNum->value();
    switch (dice_num) {
        case 1:{
            num3 = qrand()%6;   //随机生成0-5之间的数
            showGif3(num3);
            break;
        }
        case 2:{
            num1 = qrand()%6;   //随机生成0-5之间的数
            num2 = qrand()%6;
            showGif1(num1);
            showGif2(num2);
            break;
        }
        case 3:{
            num1 = qrand()%6;   //随机生成0-5之间的数
            num2 = qrand()%6;
            num3 = qrand()%6;
            showGif1(num1);
            showGif2(num2);
            showGif3(num3);
            break;
        }
        case 4:{
            num1 = qrand()%6;   //随机生成0-5之间的数
            num2 = qrand()%6;
            num3 = qrand()%6;
            num4 = qrand()%6;
            showGif1(num1);
            showGif2(num2);
            showGif3(num3);
            showGif4(num4);
            break;
        }
        case 5:{
            num1 = qrand()%6;   //随机生成0-5之间的数
            num2 = qrand()%6;
            num3 = qrand()%6;
            num4 = qrand()%6;
            num5 = qrand()%6;
            showGif1(num1);
            showGif2(num2);
            showGif3(num3);
            showGif4(num4);
            showGif5(num5);
            break;
        }
    }

}

void diceGame::clearLabel()
{
    ui->label1->clear();
    ui->label2->clear();
    ui->label3->clear();
    ui->label4->clear();
    ui->label5->clear();
}


//设置背景图片
void diceGame::paintEvent(QPaintEvent *)
{
//    QPainter painter(this);
//    QPixmap pix;
//    pix.load("../diceGame/bg_pic.jpg");
//    painter.drawPixmap(0, 0, 800, 600, pix);
}

