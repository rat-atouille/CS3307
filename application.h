#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "layerManager.h"
#include "project.h"
#include "Brush.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class Application : public QMainWindow {
    Q_OBJECT

public:
    Application(QWidget* parent = nullptr);
    ~Application();

private slots:
    // menus
    void exporting(QString type);
    void on_actionCreate_new_triggered();
    void on_actionOpen_triggered();
    void on_actionPSD_triggered();
    void on_actionJPEG_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();

private:

    Ui::Application* ui;

    LayerManager* layerManager;
    Project* project;
    std::unique_ptr<Brush> currentBrush;

    QString currentFile = "";

    void setupBrushControls();
    void setupMainWindow();
    void createConnections();
};

#endif // APPLICATION_H
