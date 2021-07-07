#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCoreApplication>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dataPath = QCoreApplication::applicationDirPath()+"/db5.db";
    db.setDatabaseName(dataPath);
    if(!db.open())
    {
        QMessageBox::critical(0,"cannot open database","Unable to establish a database connection.",
                              QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    query.exec("create table tb(id int primary key,operation varchar,inStation_led varchar,pos_led varchar,datetime varchar)");
    query.exec("insert into tb values(1,'正轨','黄','绿','2021-05-02 19:22:12')");
    return true;
}

#endif // CONNECTION_H
