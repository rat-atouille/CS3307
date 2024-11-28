#ifndef ERASER_H
#define ERASER_H

#include "Brush.h"

class Eraser : public Brush {
public:
    Eraser(int size)
        : Brush(size, QColor(Qt::white)) {} // Eraser is always white

    void paint(QPainter& painter, const QPoint& position) override {
        QPen pen(Qt::white); // Set color to white for erasing
        pen.setWidth(brushSize);
        painter.setPen(pen);
        painter.drawPoint(position);
    }
};

#endif // ERASER_H
