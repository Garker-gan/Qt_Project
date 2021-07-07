#ifndef DICEGAME_H
#define DICEGAME_H

#include <QMainWindow>
#include <QLabel>
#include <QMovie>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class diceGame; }
QT_END_NAMESPACE

class diceGame : public QMainWindow
{
    Q_OBJECT

public:
    diceGame(QWidget *parent = nullptr);
    ~diceGame();
    //骰子数目为1
    void showGif1(int num);
    //骰子数目为2
    void showGif2(int num);
    //骰子数目为3
    void showGif3(int num);
    //骰子数目为4
    void showGif4(int num);
    //骰子数目为5
    void showGif5(int num);

    void clearLabel();

    //设置背景图片
    void paintEvent(QPaintEvent *);

private slots:
    void on_start_clicked();

private:
    Ui::diceGame *ui;
};
#endif // DICEGAME_H
