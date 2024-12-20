
#include "LayerManagerDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

// manages layer managment logic including reorder, create, delete, update in the layer list
LayerManagerDialog::LayerManagerDialog(LayeredCanvas* canvas, QWidget* parent)
    : QDialog(parent), targetCanvas(canvas) {

    setWindowTitle("Layer Manager");

    // Layer List
    layerList = new QListWidget(this);

    // Layer Name Edit
    layerNameEdit = new QLineEdit(this);
    layerNameEdit->setPlaceholderText("Enter layer name");

    // Buttons
    addLayerBtn = new QPushButton("Add Layer", this);
    deleteLayerBtn = new QPushButton("Delete Layer", this);
    clearLayerBtn = new QPushButton("Clear Layer", this);
    visibilityToggleBtn = new QPushButton("Toggle Visibility", this);
    renameLayerBtn = new QPushButton("Rename Layer", this);

    // Opacity Slider
    opacitySlider = new QSlider(Qt::Horizontal, this);
    opacitySlider->setRange(0, 100);
    opacitySlider->setValue(100);
    QLabel* opacityLabel = new QLabel("Layer Opacity", this);

    // Layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addLayerBtn);
    buttonLayout->addWidget(deleteLayerBtn);
    buttonLayout->addWidget(clearLayerBtn);
    buttonLayout->addWidget(visibilityToggleBtn);

    QHBoxLayout* renameLayout = new QHBoxLayout();
    renameLayout->addWidget(layerNameEdit);
    renameLayout->addWidget(renameLayerBtn);

    QHBoxLayout* opacityLayout = new QHBoxLayout();
    opacityLayout->addWidget(opacityLabel);
    opacityLayout->addWidget(opacitySlider);

    mainLayout->addWidget(layerList);
    mainLayout->addLayout(renameLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(opacityLayout);

    // Add move layer buttons
    moveUpBtn = new QPushButton("Move Up", this);
    moveDownBtn = new QPushButton("Move Down", this);

    buttonLayout->addWidget(moveUpBtn);
    buttonLayout->addWidget(moveDownBtn);

    // reorder layer
    connect(moveUpBtn, &QPushButton::clicked, this, &LayerManagerDialog::moveLayerUp);
    connect(moveDownBtn, &QPushButton::clicked, this, &LayerManagerDialog::moveLayerDown);

    // Connections
    connect(addLayerBtn, &QPushButton::clicked, this, &LayerManagerDialog::addLayer);
    connect(deleteLayerBtn, &QPushButton::clicked, this, &LayerManagerDialog::deleteLayer);
    connect(clearLayerBtn, &QPushButton::clicked, this, &LayerManagerDialog::clearLayer);  // Connect clear layer button
    connect(visibilityToggleBtn, &QPushButton::clicked, this, &LayerManagerDialog::toggleVisibility);
    connect(renameLayerBtn, &QPushButton::clicked, this, &LayerManagerDialog::renameLayer);
    connect(layerList, &QListWidget::currentRowChanged, this, &LayerManagerDialog::currentLayerChanged);
    connect(targetCanvas, &LayeredCanvas::layersChanged, this, &LayerManagerDialog::updateLayerList);
    connect(opacitySlider, &QSlider::valueChanged, this, &LayerManagerDialog::updateLayerOpacity);

    updateLayerList();
}

// add layer & update the layer list
void LayerManagerDialog::addLayer() {
    targetCanvas->addNewLayer();
}

// delete layer & update the layer list
void LayerManagerDialog::deleteLayer() {
    targetCanvas->deleteCurrentLayer();
}


// clear all the drawing on the layer
void LayerManagerDialog::clearLayer() {
    int currentRow = layerList->currentRow();
    if (currentRow >= 0) {
        // Confirm before clearing
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  "Clear Layer",
                                                                  "Are you sure you want to clear the current layer?",
                                                                  QMessageBox::Yes | QMessageBox::No
                                                                  );

        if (reply == QMessageBox::Yes) {
            // Clear the current layer's image
            auto& layers = const_cast<QVector<Layer>&>(targetCanvas->getLayers());
            layers[currentRow].image.fill(Qt::transparent);

            // Update the canvas
            targetCanvas->update();
        }
    }
}

// change the visiblity of the selected layer
void LayerManagerDialog::toggleVisibility() {
    int currentRow = layerList->currentRow();
    if (currentRow >= 0) {
        targetCanvas->toggleLayerVisibility(currentRow);
    }
}

// rename layer
void LayerManagerDialog::renameLayer() {
    int currentRow = layerList->currentRow();
    if (currentRow >= 0) {
        QString newName = layerNameEdit->text();
        if (!newName.isEmpty()) {
            targetCanvas->renameLayer(currentRow, newName);
            layerNameEdit->clear();
        }
    }
}

// track if user changed (draw, erase, rename etc) on the layer
void LayerManagerDialog::currentLayerChanged(int row) {
    targetCanvas->setCurrentLayer(row);

    // Update opacity slider when layer changes
    const auto& layers = targetCanvas->getLayers();
    if (row >= 0 && row < layers.size()) {
        opacitySlider->setValue(layers[row].opacity * 100);
    }
}

// update layer list when reorder or delete, create layer occurs
void LayerManagerDialog::updateLayerList() {
    layerList->clear();
    const auto& layers = targetCanvas->getLayers();
    const auto& layerNames = targetCanvas->getLayerNames();
    for (int i = 0; i < layers.size(); ++i) {
        QListWidgetItem* item = new QListWidgetItem(layerNames[i]);
        layerList->addItem(item);
    }
}

// update the layer opactiy from GUI input
void LayerManagerDialog::updateLayerOpacity(int value) {
    int currentRow = layerList->currentRow();
    if (currentRow >= 0) {
        // Convert slider value (0-100) to opacity (0.0-1.0)
        qreal opacity = value / 100.0;
        // Update layer opacity
        auto& layers = const_cast<QVector<Layer>&>(targetCanvas->getLayers());
        layers[currentRow].opacity = opacity;
        targetCanvas->update();
    }
}

// move layer up
void LayerManagerDialog::moveLayerUp() {
    int currentRow = layerList->currentRow();
    if (currentRow > 0) {
        targetCanvas->moveLayer(currentRow, currentRow - 1);
        layerList->setCurrentRow(currentRow - 1);
    }
}

// move layer down
void LayerManagerDialog::moveLayerDown() {
    int currentRow = layerList->currentRow();
    if (currentRow < layerList->count() - 1) {
        targetCanvas->moveLayer(currentRow, currentRow + 1);
        layerList->setCurrentRow(currentRow + 1);
    }
}
