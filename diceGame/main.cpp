#include "dicegame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    diceGame w;
    w.show();
    return a.exec();
}
