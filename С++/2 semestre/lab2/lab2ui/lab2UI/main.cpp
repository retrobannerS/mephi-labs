#include "lab2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lab2ui w;
    w.show();
    return a.exec();
}
