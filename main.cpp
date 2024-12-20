#include "PaintApplication.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintApplication w;
    w.show();
    return a.exec();
}
