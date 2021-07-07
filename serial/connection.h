#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCoreApplication>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dataPath = QCoreApplication::applicationDirPath()+"/my.db";
    db.setDatabaseName(dataPath);
    if(!db.open())
    {
        QMessageBox::critical(0,"cannot open database","Unable to establish a database connection.",
                              QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    query.exec("create table s2(id int primary key,name varchar,temp float,date varchar)");
    query.exec("insert into s2 values(1,'李强',36.5,20210415)");
    query.exec("insert into s2 values(2,'马亮',37.3,20210416)");
    query.exec("insert into s2 values(3,'孙红',36.4,20210417)");
    query.exec("insert into s2 values(4,'孙红',36.7,20210418)");
    return true;
}

#endif // CONNECTION_H
