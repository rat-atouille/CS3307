#ifndef PEN_H
#define PEN_H

#include "Brush.h"

// Derived class from Brush
class Pen : public Brush {
public:
    Pen(int size, const QColor& color)
        : Brush(size, color) {}

    void paint(QPainter& painter, const QPoint& position) override {
        QPen pen(brushColor);
        pen.setWidth(brushSize);
        painter.setPen(pen);
        painter.drawPoint(position);
    }
};

#endif // PEN_H
