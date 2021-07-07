#include "serial.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnection()) return 1;

    Serial w;
    w.show();
    return a.exec();
}
