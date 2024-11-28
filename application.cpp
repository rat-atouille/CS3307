#include "application.h"
#include "ui_application.h"
#include "layerManager.h"
#include "brushFactory.h"

#include <QComboBox>
#include <QSlider>

Application::Application(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Application), project(nullptr) {
    ui->setupUi(this);


    // Initialize LayerManager
    layerManager = &LayerManager::getInstance();

    // Initialize Project with LayerManager
    project = new Project(layerManager, this);
    setCentralWidget(project);

    createConnections();
    setupMainWindow();
    setupBrushControls();

}

Application::~Application() {
    delete ui;
}

void Application::setupMainWindow() {
    setWindowTitle("Paint Application");

}

void Application::setupBrushControls() {

}

void Application::on_actionCreate_new_triggered() {
    currentFile.clear();
}

void Application::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("Project Files (*.proj)"));
    if (!fileName.isEmpty()) {
        // Load logic here
    }
}

void Application::on_actionSave_triggered() {
    if (currentFile.isEmpty()) {
        on_actionSave_as_triggered();
    } else {
        // Save logic here
    }
}

void Application::on_actionSave_as_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("Project Files (*.proj)"));
    if (!fileName.isEmpty()) {
        currentFile = fileName;
        on_actionSave_triggered();
    }
}

void Application::exporting(QString type) {
    if (type == "PSD") {
        // Export as PSD logic
    } else if (type == "JPEG") {
        // Export as JPEG logic
    }
}

void Application::on_actionPSD_triggered() {
    exporting("PSD");
}

void Application::on_actionJPEG_triggered() {
    exporting("JPEG");
}

void Application::createConnections() {
    connect(ui->actionCreate_new, &QAction::triggered, this, &Application::on_actionCreate_new_triggered);
    connect(ui->actionOpen, &QAction::triggered, this, &Application::on_actionOpen_triggered);
    connect(ui->actionSave, &QAction::triggered, this, &Application::on_actionSave_triggered);
    connect(ui->actionSave_as, &QAction::triggered, this, &Application::on_actionSave_as_triggered);
}
