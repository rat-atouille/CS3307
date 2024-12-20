// brushtool.cpp
#include "brushtool.h"

std::unique_ptr<BrushTool> BrushTool::createBrush(BrushType type) {
    switch(type) {
    case PEN: return std::make_unique<PenBrush>();
    case ERASER: return std::make_unique<EraserBrush>();
    default: return std::make_unique<PenBrush>();
    }
}

void PenBrush::draw(QPainter& painter, const QPointF& point) {
    painter.setPen(QPen(m_color, m_size, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(point);
}

void PenBrush::setColor(const QColor& color) {
    m_color = color;
}

void PenBrush::setSize(int size) {
    m_size = size;
}

void EraserBrush::draw(QPainter& painter, const QPointF& point) {
    painter.setPen(QPen(Qt::white, m_size, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(point);
}

void EraserBrush::setColor(const QColor&) {
    // Eraser always uses white
}

void EraserBrush::setSize(int size) {
    m_size = size;
}
