#include "toolbar.h"

#include <QVBoxLayout>
#include <QComboBox>

// Constructor
Toolbar::Toolbar(QWidget* parent) : QWidget(parent), activeTool(nullptr), brushTool(new Brush()), eraserTool(new Eraser()) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    toolComboBox = new QComboBox(this);
    toolComboBox->addItem("Brush Tool");
    toolComboBox->addItem("Eraser Tool");

    layout->addWidget(toolComboBox);
    setLayout(layout);

    connect(toolComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onToolChanged(int)));
    onToolChanged(toolComboBox->currentIndex());  // Set default tool
}

// Destructor
Toolbar::~Toolbar() {
    delete brushTool;
    delete eraserTool;
}

// Handle tool change
void Toolbar::onToolChanged(int index) {
    switch (index) {
    case 0:
        activeTool = brushTool;
        break;
    case 1:
        activeTool = eraserTool;
        break;
    }
}

// Get the active tool
Tool* Toolbar::getActiveTool() const {
    return activeTool;
}
