// canvas.cpp
#include "canvas.h"
#include <QMouseEvent>
#include <QDebug>

Canvas::Canvas(QWidget* parent) : QWidget(parent) {
    // Set up the canvas
    setMinimumSize(800, 600);
    setMouseTracking(true);

    // Default to pen brush
    m_currentBrush = BrushTool::createBrush(BrushTool::PEN);

    // Register with LayerManager
    LayerManager::getInstance().addObserver(this);
}

void Canvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);

    // Render layers in order
    auto& layers = LayerManager::getInstance().getLayers();

    for (auto& layer : layers) {
        if (layer.isVisible()) {
            painter.drawImage(0, 0, layer.getImage());
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_lastPos = event->pos();

        // Get active layer
        auto& layerManager = LayerManager::getInstance();
        int activeIndex = layerManager.getActiveLayerIndex();

        if (activeIndex >= 0) {
            QPainter layerPainter(&layerManager.getLayers()[activeIndex].getImage());
            m_currentBrush->draw(layerPainter, m_lastPos);

            update(); // Trigger repaint
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        // Get active layer
        auto& layerManager = LayerManager::getInstance();
        int activeIndex = layerManager.getActiveLayerIndex();

        if (activeIndex >= 0) {
            QPainter layerPainter(&layerManager.getLayers()[activeIndex].getImage());

            // Draw a line from last position to current position
            layerPainter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
            layerPainter.drawLine(m_lastPos, event->pos());

            m_lastPos = event->pos();
            update(); // Trigger repaint
        }
    }
}

void Canvas::setBrushTool(BrushTool::BrushType type) {
    m_currentBrush = BrushTool::createBrush(type);
}

void Canvas::onLayerChanged() {
    // Repaint when layers are modified
    update();
}
