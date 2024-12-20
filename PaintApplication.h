#ifndef PAINT_APPLICATION_H
#define PAINT_APPLICATION_H

#include <QMainWindow>
#include <QToolBar>
#include <QSlider>
#include "LayeredCanvas.h"
#include "LayerManagerDialog.h"

// This class implements the user interface and logic for each GUI
class PaintApplication : public QMainWindow {
    Q_OBJECT

public:
    PaintApplication(QWidget* parent = nullptr);

private:
    void createToolBar();
    void createMenus();
    void createActions();

    // File Operations
    void saveProject();
    void saveAsProject();
    void loadProject();
    void exportImage();
    void autoSaveProject();

    // Tool Operations
    void showColorPicker();
    void adjustToolSize();
    void openLayerManager();

    // auto save
    QTimer* autosaveTimer;
    QString currentProjectFileName;
    bool hasUnsavedChanges;
    void markUnsavedChanges();
    void updateWindowTitle();

    LayeredCanvas* canvas;
    QSlider* toolSizeSlider;

    // Actions
    QAction* saveProjectAct;
    QAction* saveAsProjectAct;
    QAction* loadProjectAct;
    QAction* exportImageAct;
    QAction* colorPickerAct;
    QAction* toolSizeAct;
    QAction* resizeCanvasAct;

private slots:
    void showResizeDialog();    // for resizing canvas
};

#endif // PAINT_APPLICATION_H

