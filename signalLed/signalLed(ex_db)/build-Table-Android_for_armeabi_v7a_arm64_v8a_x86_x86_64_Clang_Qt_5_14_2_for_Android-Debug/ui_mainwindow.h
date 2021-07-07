/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *lab_status;
    QPushButton *btn_delete;
    QPushButton *go;
    QTableView *tableView;
    QComboBox *cmd_port_name;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *Yellow;
    QLabel *Green;
    QPushButton *btn_add;
    QLabel *YELLOW_1;
    QLabel *GREEN;
    QLabel *RED;
    QLabel *YELLOW_2;
    QLabel *WHITE;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QLabel *rail1;
    QLabel *rail2;
    QLabel *rail4;
    QLabel *rail3;
    QLCDNumber *lcdNumber;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 608);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lab_status = new QLabel(centralwidget);
        lab_status->setObjectName(QString::fromUtf8("lab_status"));
        lab_status->setGeometry(QRect(10, 10, 67, 17));
        btn_delete = new QPushButton(centralwidget);
        btn_delete->setObjectName(QString::fromUtf8("btn_delete"));
        btn_delete->setGeometry(QRect(710, 490, 89, 25));
        go = new QPushButton(centralwidget);
        go->setObjectName(QString::fromUtf8("go"));
        go->setGeometry(QRect(190, 10, 89, 25));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 360, 691, 191));
        cmd_port_name = new QComboBox(centralwidget);
        cmd_port_name->addItem(QString());
        cmd_port_name->addItem(QString());
        cmd_port_name->addItem(QString());
        cmd_port_name->addItem(QString());
        cmd_port_name->setObjectName(QString::fromUtf8("cmd_port_name"));
        cmd_port_name->setGeometry(QRect(80, 10, 72, 25));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(350, 280, 81, 81));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        Yellow = new QLabel(verticalLayoutWidget_3);
        Yellow->setObjectName(QString::fromUtf8("Yellow"));

        verticalLayout_3->addWidget(Yellow);

        Green = new QLabel(verticalLayoutWidget_3);
        Green->setObjectName(QString::fromUtf8("Green"));

        verticalLayout_3->addWidget(Green);

        btn_add = new QPushButton(centralwidget);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));
        btn_add->setGeometry(QRect(710, 410, 89, 25));
        YELLOW_1 = new QLabel(centralwidget);
        YELLOW_1->setObjectName(QString::fromUtf8("YELLOW_1"));
        YELLOW_1->setGeometry(QRect(50, 60, 79, 39));
        GREEN = new QLabel(centralwidget);
        GREEN->setObjectName(QString::fromUtf8("GREEN"));
        GREEN->setGeometry(QRect(50, 100, 79, 50));
        RED = new QLabel(centralwidget);
        RED->setObjectName(QString::fromUtf8("RED"));
        RED->setGeometry(QRect(50, 140, 79, 31));
        YELLOW_2 = new QLabel(centralwidget);
        YELLOW_2->setObjectName(QString::fromUtf8("YELLOW_2"));
        YELLOW_2->setGeometry(QRect(50, 220, 79, 31));
        WHITE = new QLabel(centralwidget);
        WHITE->setObjectName(QString::fromUtf8("WHITE"));
        WHITE->setGeometry(QRect(50, 180, 79, 31));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(660, 280, 72, 15));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(660, 150, 72, 15));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(350, 30, 104, 41));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(360, 90, 93, 28));
        rail1 = new QLabel(centralwidget);
        rail1->setObjectName(QString::fromUtf8("rail1"));
        rail1->setGeometry(QRect(40, 270, 72, 15));
        rail2 = new QLabel(centralwidget);
        rail2->setObjectName(QString::fromUtf8("rail2"));
        rail2->setGeometry(QRect(230, 120, 21, 81));
        rail4 = new QLabel(centralwidget);
        rail4->setObjectName(QString::fromUtf8("rail4"));
        rail4->setGeometry(QRect(240, 120, 72, 15));
        rail3 = new QLabel(centralwidget);
        rail3->setObjectName(QString::fromUtf8("rail3"));
        rail3->setGeometry(QRect(240, 270, 72, 15));
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(620, 50, 64, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lab_status->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267", nullptr));
        btn_delete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        go->setText(QCoreApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        cmd_port_name->setItemText(0, QCoreApplication::translate("MainWindow", "COM1", nullptr));
        cmd_port_name->setItemText(1, QCoreApplication::translate("MainWindow", "COM2", nullptr));
        cmd_port_name->setItemText(2, QCoreApplication::translate("MainWindow", "COM3", nullptr));
        cmd_port_name->setItemText(3, QCoreApplication::translate("MainWindow", "COM4", nullptr));

        cmd_port_name->setCurrentText(QCoreApplication::translate("MainWindow", "COM1", nullptr));
        Yellow->setText(QCoreApplication::translate("MainWindow", "Yellow", nullptr));
        Green->setText(QCoreApplication::translate("MainWindow", "Green", nullptr));
        btn_add->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        YELLOW_1->setText(QCoreApplication::translate("MainWindow", "YELLOW_1", nullptr));
        GREEN->setText(QCoreApplication::translate("MainWindow", "GREEN", nullptr));
        RED->setText(QCoreApplication::translate("MainWindow", "RED", nullptr));
        YELLOW_2->setText(QCoreApplication::translate("MainWindow", "YELLOW_2", nullptr));
        WHITE->setText(QCoreApplication::translate("MainWindow", "WHITE", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\255\243\347\272\277", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\344\276\247\347\272\277", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Go", nullptr));
        rail1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        rail2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        rail4->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        rail3->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
