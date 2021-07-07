#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCoreApplication>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dataPath = QCoreApplication::applicationDirPath()+"/db.db";
    db.setDatabaseName(dataPath);
    if(!db.open())
    {
        QMessageBox::critical(0,"cannot open database","Unable to establish a database connection.",
                              QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    query.exec("create table tb1(id int primary key,section varchar,datetime varchar)");
    query.exec("insert into tb1 values(1,'001','2021-04-22 09:12:32')");
    query.exec("insert into tb1 values(2,'002','2021-04-22 12:52:42')");
    query.exec("insert into tb1 values(3,'003','2021-04-23 15:42:34')");
    query.exec("insert into tb1 values(4,'004','2021-04-24 23:32:36')");
    return true;
}

#endif // CONNECTION_H
