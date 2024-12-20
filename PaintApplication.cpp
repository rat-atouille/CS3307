
#include "PaintApplication.h"
#include <QMenuBar>
#include <QAction>
#include <QColorDialog>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QFileDialog>

#include <QMessageBox>
#include <QFileInfo>
#include <QTimer>
#include <QStandardPaths>
#include <QSpinBox>

// This class implements the user interface and logic for each GUI
PaintApplication::PaintApplication(QWidget* parent) : QMainWindow(parent) {
    canvas = new LayeredCanvas(this);
    setCentralWidget(canvas);

    createToolBar();    // for brush tool & layer manager
    createMenus();      // for save, load, resize, export logic

    // Autosave setup
    autosaveTimer = new QTimer(this);
    connect(autosaveTimer, &QTimer::timeout, this, &PaintApplication::autoSaveProject);
    autosaveTimer->start(5 * 60 * 1000); // Autosave every 5 minutes

    // Track if project has unsaved changes
    currentProjectFileName = "";
    hasUnsavedChanges = false;

    // Connect canvas changes to track modifications
    connect(canvas, &LayeredCanvas::layersChanged, this, &PaintApplication::markUnsavedChanges);

    resize(800, 600);      // default canvas size
}

// create tool bar needed for drawing
// add pen, eraser, fill bucket, ajudst size, layer manager to tool bar
void PaintApplication::createToolBar() {
    QToolBar* toolbar = addToolBar("Tools");

    // Pen tool
    QAction* penAction = toolbar->addAction("Pen");
    connect(penAction, &QAction::triggered, [this]() {
        canvas->setTool(DrawingToolFactory::Pen);
    });

    // Eraser tool
    QAction* eraserAction = toolbar->addAction("Eraser");
    connect(eraserAction, &QAction::triggered, [this]() {
        canvas->setTool(DrawingToolFactory::Eraser);
    });

    // Pen Size
    toolSizeAct = toolbar->addAction("Tool Size");
    connect(toolSizeAct, &QAction::triggered, this, &PaintApplication::adjustToolSize);

    // Color Picker
    colorPickerAct = toolbar->addAction("Color");
    connect(colorPickerAct, &QAction::triggered, this, &PaintApplication::showColorPicker);

    QAction* fillBucketAction = toolbar->addAction("Fill Bucket");
    connect(fillBucketAction, &QAction::triggered, [this]() {
        canvas->setTool(DrawingToolFactory::FillBucket);
    });
    // Layer Manager
    QAction* layerManagerAction = toolbar->addAction("Layer Manager");
    connect(layerManagerAction, &QAction::triggered, this, &PaintApplication::openLayerManager);

}

// create GUI menu for save, saveAs, load, export, resize logic
void PaintApplication::createMenus() {

    // create actions
    saveAsProjectAct = new QAction("Save As", this);
    connect(saveAsProjectAct, &QAction::triggered, this, &PaintApplication::saveAsProject);

    saveProjectAct = new QAction("Save", this);
    connect(saveProjectAct, &QAction::triggered, this, &PaintApplication::saveProject);

    loadProjectAct = new QAction("Load Project", this);
    connect(loadProjectAct, &QAction::triggered, this, &PaintApplication::loadProject);

    exportImageAct = new QAction("Export Image", this);
    connect(exportImageAct, &QAction::triggered, this, &PaintApplication::exportImage);

    // File Menu
    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(saveProjectAct);
    fileMenu->addAction(saveAsProjectAct);
    fileMenu->addAction(loadProjectAct);
    fileMenu->addAction(exportImageAct);

    // resize
    QMenu* editMenu = menuBar()->addMenu("&Edit");
    resizeCanvasAct = new QAction("Resize Canvas", this);
    connect(resizeCanvasAct, &QAction::triggered, this, &PaintApplication::showResizeDialog);
    editMenu->addAction(resizeCanvasAct);
}

// show color picker/palette for pen/fill bucket tool
void PaintApplication::showColorPicker() {
    QColor color = QColorDialog::getColor(Qt::black, this, "Pick Pen Color");
    if (color.isValid()) {
        canvas->setPenColor(color);
    }
}

// open layer manager
void PaintApplication::openLayerManager() {
    LayerManagerDialog* layerDialog = new LayerManagerDialog(canvas, this);
    layerDialog->show();
}


// GUI for adjusting the tool size
// use slider from 1 to 20
void PaintApplication::adjustToolSize() {
    QDialog sizeDialog(this);
    sizeDialog.setWindowTitle("Adjust Tool Size");

    QVBoxLayout* layout = new QVBoxLayout(&sizeDialog);

    QLabel* label = new QLabel("Tool Size:", &sizeDialog);
    layout->addWidget(label);

    QSlider* slider = new QSlider(Qt::Horizontal, &sizeDialog);
    slider->setRange(1, 20);
    slider->setValue(canvas->getPenWidth());
    layout->addWidget(slider);

    QLabel* sizeLabel = new QLabel(QString("Current Size: %1").arg(slider->value()), &sizeDialog);
    layout->addWidget(sizeLabel);

    connect(slider, &QSlider::valueChanged, [this, sizeLabel](int value) {
        canvas->setPenWidth(value);
        sizeLabel->setText(QString("Current Size: %1").arg(value));
    });

    QPushButton* closeBtn = new QPushButton("Close", &sizeDialog);
    connect(closeBtn, &QPushButton::clicked, &sizeDialog, &QDialog::accept);
    layout->addWidget(closeBtn);

    sizeDialog.exec();
}

// mark the window title with * at the end to indicate that the work has not been saved yet
void PaintApplication::markUnsavedChanges() {
    hasUnsavedChanges = true;
    updateWindowTitle();
}

// update software window title
void PaintApplication::updateWindowTitle() {
    QString title = "Paint Application";
    if (!currentProjectFileName.isEmpty()) {
        title += " - " + QFileInfo(currentProjectFileName).fileName();
    }
    if (hasUnsavedChanges) {
        title += " *";
    }
    setWindowTitle(title);
}

// autosave the project every 5 min to prevent data loss
void PaintApplication::autoSaveProject() {
    if (!hasUnsavedChanges) return;

    // Use a standard location for autosaves
    QString autosaveDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/PaintAppAutosave/";
    QDir().mkpath(autosaveDir);

    // Generate unique filename with timestamp
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString autosaveFileName = autosaveDir + "autosave_" + timestamp + ".pntprj";

    if (canvas->saveProject(autosaveFileName)) {
        qDebug() << "Autosave completed:" << autosaveFileName;
    }
}

// if the user already saved the project in local storage, overwrite the file with most recent actions
void PaintApplication::saveProject() {
    if (currentProjectFileName.isEmpty()) {
        saveAsProject();
        return;
    }

    if (canvas->saveProject(currentProjectFileName)) {
        hasUnsavedChanges = false;
        updateWindowTitle();
        QMessageBox::information(this, "Save Successful", "Project saved successfully!");
    } else {
        QMessageBox::warning(this, "Save Failed", "Could not save the project.");
    }
}

// save project as a new file
void PaintApplication::saveAsProject() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save Project",
                                                    "",
                                                    "Paint Project (*.pntprj)");

    if (!fileName.isEmpty()) {
        // Ensure .pntprj extension
        if (!fileName.endsWith(".pntprj")) {
            fileName += ".pntprj";
        }

        currentProjectFileName = fileName;
        if (canvas->saveProject(fileName)) {
            hasUnsavedChanges = false;
            updateWindowTitle();
            QMessageBox::information(this, "Save Successful", "Project saved successfully!");
        } else {
            QMessageBox::warning(this, "Save Failed", "Could not save the project.");
        }
    }
}

// load existing project (.pntprj) to the application with the layers
void PaintApplication::loadProject() {
    // Check for unsaved changes before loading
    if (hasUnsavedChanges) {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  "Unsaved Changes",
                                                                  "You have unsaved changes. Do you want to save before loading a new project?",
                                                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Cancel) return;
        if (reply == QMessageBox::Yes) saveProject();
    }

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Load Project",
                                                    "",
                                                    "Paint Project (*.pntprj)");

    if (!fileName.isEmpty()) {
        if (canvas->loadProject(fileName)) {
            currentProjectFileName = fileName;
            hasUnsavedChanges = false;
            updateWindowTitle();
        }
    }
}

// export the project as image format and save it user's desired local storage
void PaintApplication::exportImage() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Export Image",
                                                    "",
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!fileName.isEmpty()) {
        // Extract file extension for format
        QString format = QFileInfo(fileName).suffix().toLower();
        if (format.isEmpty()) {
            format = "png";  // default format
            fileName += ".png";
        }

        if (canvas->exportImage(fileName, format)) {
            QMessageBox::information(this, "Export Successful",
                                     "Image exported successfully!");
        } else {
            QMessageBox::warning(this, "Export Failed",
                                 "Could not export the image.");
        }
    }
}

// handles the input for resizing the canvas
void PaintApplication::showResizeDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Resize Canvas");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QSize currentSize = canvas->size();

    // Width input
    QHBoxLayout* widthLayout = new QHBoxLayout();
    QLabel* widthLabel = new QLabel("Width:", &dialog);
    QSpinBox* widthBox = new QSpinBox(&dialog);
    widthBox->setRange(1, 4096);
    widthBox->setValue(currentSize.width());
    widthLayout->addWidget(widthLabel);
    widthLayout->addWidget(widthBox);

    // Height input
    QHBoxLayout* heightLayout = new QHBoxLayout();
    QLabel* heightLabel = new QLabel("Height:", &dialog);
    QSpinBox* heightBox = new QSpinBox(&dialog);
    heightBox->setRange(1, 4096);
    heightBox->setValue(currentSize.height());
    heightLayout->addWidget(heightLabel);
    heightLayout->addWidget(heightBox);

    layout->addLayout(widthLayout);
    layout->addLayout(heightLayout);

    // Buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        QSize newSize(widthBox->value(), heightBox->value());
        canvas->resizeCanvas(newSize);
    }
}

