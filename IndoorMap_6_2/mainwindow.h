#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QList>
#include <QMessageBox>
#include <QImage>
#include <QGraphicsScene>
#include <QSettings>
#include <QMap>
#include "imagewidget.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void            recvShowPicSignal();

private slots:
    void on_pushButton_open_clicked();
    void showMousePos(QPointF pointf,QColor qColor,qreal qrScale);
    void recvGreViewMouseWheel(qreal qrScale);
    void on_pushButton_2_clicked();
    void getPos();
    void addLoc(float x, float y);
    void addDot(float x, float y);
    void addDot_blue(float x, float y);


    void on_getLoc_clicked();

    void Sleep(int msec);

public:

private:
    QGraphicsScene  *m_qgraphicsScene;
    ImageWidget     *m_Image;
    QVector<QGraphicsRectItem*> m_vQGRecItem;
//    QVector<QRect>    m_vRect;
    QVector<QPointF>  m_vPoint;
    Ui::MainWindow  *ui;
    QList<QImage>   m_qlistLoadImgs;
    qint32          m_nCrtIndex;
    qint32          m_nCrtAlgoID;
};

#endif // MAINWINDOW_H
