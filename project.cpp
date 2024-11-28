#include "project.h"
#include <QPainter>

#include "layerManager.h"

Project::Project(LayerManager* manager, QWidget* parent)
    : QWidget(parent), layerManager(manager) {
    setAttribute(Qt::WA_OpaquePaintEvent);  // Set transparency
}

void Project::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    layerManager->draw(painter);

    // Iterate over all layers and paint each one

}
