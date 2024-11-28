#include "application.h"
#include "brushfactory.h"
#include "layerManager.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QColorDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;

    w.show();

    return a.exec();
}
