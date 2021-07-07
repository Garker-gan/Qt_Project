#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QFileDialog>
#include <QList>
#include <QMessageBox>
#include <QImage>
#include <QGraphicsScene>
#include <QSettings>
#include <QMap>
#include "imagewidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addIcon_clicked();

    void on_getWay_clicked();

    void showPic(QImage image);

    void showMousePos(QPointF pointf,QColor qColor,qreal qrScale);

    void recvGreViewMouseWheel(qreal qrScale);

    void on_open_clicked();

    void addLoc(float x, float y);

    void getPos();

    void addDot(float x, float y);

    void addDot_blue(float x, float y);

    void Sleep(int msec);

    void on_getLoc_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene  *m_qgraphicsScene;
    ImageWidget     *m_Image;
    QList<QImage>   m_qlistLoadImgs;
    qint32          m_nCrtIndex;

    QVector<QPointF>  m_vPoint;
    QVector<QGraphicsRectItem*> m_vQGRecItem;
};
#endif // MAINWINDOW_H
