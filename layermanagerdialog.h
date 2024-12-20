
#ifndef LAYER_MANAGER_DIALOG_H
#define LAYER_MANAGER_DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include "LayeredCanvas.h"

// manages layer managment logic including reorder, create, delete, update in the layer list
class LayerManagerDialog : public QDialog {
    Q_OBJECT

public:
    LayerManagerDialog(LayeredCanvas* canvas, QWidget* parent = nullptr);

private slots:
    void addLayer();
    void deleteLayer();
    void clearLayer();  // New method for clearing layer
    void toggleVisibility();
    void renameLayer();
    void currentLayerChanged(int row);
    void updateLayerList();
    void updateLayerOpacity(int value);
    void moveLayerUp();
    void moveLayerDown();
private:
    QPushButton* moveUpBtn;
    QPushButton* moveDownBtn;
    LayeredCanvas* targetCanvas;
    QListWidget* layerList;
    QPushButton* addLayerBtn;
    QPushButton* deleteLayerBtn;
    QPushButton* clearLayerBtn;  // New button for clearing layer
    QPushButton* visibilityToggleBtn;
    QPushButton* renameLayerBtn;
    QLineEdit* layerNameEdit;
    QSlider* opacitySlider;
};

#endif // LAYER_MANAGER_DIALOG_H


