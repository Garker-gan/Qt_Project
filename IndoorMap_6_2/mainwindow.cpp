#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_Image(nullptr),
    ui(new Ui::MainWindow),
    m_nCrtIndex(0),
    m_nCrtAlgoID(1)
{
    ui->setupUi(this);
    m_qgraphicsScene = new QGraphicsScene;//要用QGraphicsView就必须要有QGraphicsScene搭配着用
}

MainWindow::~MainWindow()
{
    if(m_qgraphicsScene)
    {
        delete m_qgraphicsScene;
    }
    delete ui;
}

void MainWindow::recvShowPicSignal()
{
    QImage image("../IndoorMap_6_2/newmap.png");
    QPixmap ConvertPixmap=QPixmap::fromImage(image);//The QPixmap class is an off-screen image representation that can be used as a paint device
    m_qgraphicsScene->clear();
    m_Image = new ImageWidget(&ConvertPixmap);//实例化类ImageWidget的对象m_Image，该类继承自QGraphicsItem，是自己写的类
    QObject::connect(m_Image,&ImageWidget::showPos,this,&MainWindow::showMousePos);
    QObject::connect(m_Image,&ImageWidget::mouseWheelSig,this,&MainWindow::recvGreViewMouseWheel);
    int nwith = ui->ImageGraphic->width();//获取界面控件Graphics View的宽度
    int nheight = ui->ImageGraphic->height();//获取界面控件Graphics View的高度
    m_Image->setQGraphicsViewWH(nwith,nheight);//将界面控件Graphics View的width和height传进类m_Image中
    m_Image->setAcceptHoverEvents(true);

    m_qgraphicsScene->addItem(m_Image);//将1QGraphicsItem类对象放进QGraphicsScene中

    ui->ImageGraphic->setSceneRect(QRectF(-(nwith/2),-(nheight/2),nwith,nheight));//使视窗的大小固定在原始大小，不会随图片的放大而放大（默认状态下图片放大的时候视窗两边会自动出现滚动条，并且视窗内的视野会变大），防止图片放大后重新缩小的时候视窗太大而不方便观察图片
    ui->ImageGraphic->setScene(m_qgraphicsScene);//Sets the current scene to scene. If scene is already being viewed, this function does nothing.
    ui->ImageGraphic->setFocus();//将界面的焦点设置到当前Graphics View控件
    ui->ImageGraphic->setMouseTracking(true);
}

void MainWindow::showMousePos(QPointF pointf, QColor qColor, qreal qrScale)
{
    QString sMousePos;
    sMousePos = QString("X:%1,Y:%2,GrayLevel:%3").arg(pointf.x()).arg(pointf.y()).arg(qColor.red());
    ui->ImageGraphic->setToolTip(sMousePos);
    //m_GraphicView->setWindowTitle(sMousePos);
    QString sScale = QString::number(qrScale*100, 'f', 2);
    sScale = "  Scaling : "+ sScale +"%";
    //QString sScale = QString("  Scaling : %1 %").arg(qrScale*100);
    ui->labelScaling->setText(sScale);

}

void MainWindow::recvGreViewMouseWheel(qreal qrScale)
{
    qreal tempScale = m_Image->m_scaleDafault/qrScale;
    for(int i=0;i<m_vQGRecItem.size();i++)
    {
        m_vQGRecItem[i]->setScale(tempScale);
        QRectF rect = m_vQGRecItem[i]->rect();
        m_vQGRecItem[i]->setRect(m_vPoint[i].x()/tempScale-20,m_vPoint[i].y()/tempScale-20,rect.width(),rect.height());
    }
}
void MainWindow::on_pushButton_open_clicked()
{
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->setWindowTitle("Choose Pictures");
    QStringList qstrFilters;
    qstrFilters<<"Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)";
    qstrFilters<<"Any files (*)";
    fileDlg->setNameFilters(qstrFilters);//设置文件过滤器
    fileDlg->setFileMode(QFileDialog::ExistingFiles);//设置能选择多个文件，如果是单个文件就写成QFileDialog::ExistingFile
    if(fileDlg->exec() == QDialog::Accepted)
    {
        QStringList strPathList = fileDlg->selectedFiles();
        if(!m_qlistLoadImgs.empty())
        {
            m_qlistLoadImgs.clear();
        }
        QPixmap pixmapTemp;
        for(int i = 0;i<strPathList.count();i++)//导入一张461kb图片后，该循环增加内存占用8972kb
        {
            pixmapTemp.load(strPathList[i]);
            m_qlistLoadImgs.push_back(pixmapTemp.toImage());
        }

        if(!m_qlistLoadImgs.isEmpty())
        {
            m_nCrtIndex = 0;
//            recvShowPicSignal(m_qlistLoadImgs.at(m_nCrtIndex));
        }

    }
    else
    {
        QMessageBox mesg;
        mesg.warning(this,"警告","打开图片失败!");
    }
    fileDlg->close();
    delete fileDlg;
    fileDlg = nullptr;
}




void MainWindow::on_pushButton_2_clicked()
{
//    获取输入的下坐标
    float x = ui->x->toPlainText().toFloat();
    float y = ui->y->toPlainText().toFloat();
//    根据坐标添加定位图标
    // 定义一个 item
    addLoc(x,y);
//    switchMap(x,y);
}

void MainWindow::getPos()
{
    float x,y;
    float x_former,y_former;
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open File"),tr(""),tr("Text File (*.txt)"));

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    int count = 0;
    while(!file.atEnd()) {
        Sleep(1000);
//        每次循环后在打点，这样最后一个点就在循环体外打的是坐标点
        if(count > 0)
        {
            addDot_blue(x,y);
        }
        if(count > 1)
        {
            addDot_blue(x,y);
            addDot(x_former,y_former);
        }
        x_former = x;
        y_former = y;
//        if(count)
        count++;
        QByteArray line = file.readLine();
        QString str(line);
        qDebug()<< line;
        if(line.contains(" "))
        {

            QString strX = line.left(line.indexOf(" "));
            x = strX.toFloat();

            QString strY = line.mid(line.indexOf(" ")+1);
            y = strY.toFloat();

        }
    }
    addDot(x_former,y_former);
    addLoc(x,y);
}

void MainWindow::addLoc(float x, float y)
{
    QGraphicsPixmapItem *pItem = new QGraphicsPixmapItem(m_Image);

    QPixmap image("../IndoorMap/location.png");
    pItem->setPixmap(image.scaled(20, 25));
    pItem->setOffset(x, y);

    m_qgraphicsScene->addItem(pItem);
}

void MainWindow::addDot(float x, float y)
{
    QGraphicsPixmapItem *pItem = new QGraphicsPixmapItem(m_Image);
    QPixmap image("../IndoorMap/dot.png");
    pItem->setPixmap(image.scaled(30, 30));
    pItem->setOffset(x, y);

    m_qgraphicsScene->addItem(pItem);
}

void MainWindow::addDot_blue(float x, float y)
{
    QGraphicsPixmapItem *pItem = new QGraphicsPixmapItem(m_Image);

    QPixmap image("../IndoorMap/new_dot.png");
    pItem->setPixmap(image.scaled(30, 30));
    pItem->setOffset(x, y);

    m_qgraphicsScene->addItem(pItem);
}

void MainWindow::on_getLoc_clicked()
{
    getPos();
}



//延时函数
void MainWindow::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


