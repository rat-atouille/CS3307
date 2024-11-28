#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>

#include <QMainWindow>

QT_BEGIN_NAMESPACE


namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};


#endif // MAINWINDOW_H
