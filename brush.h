#ifndef BRUSH_H
#define BRUSH_H

#include <QPainter>
#include <QColor>

// Abstract class for Brush
class Brush {
public:
    Brush(int size, const QColor& color)
        : brushSize(size), brushColor(color) {}

    virtual ~Brush() {}

    // Pure virtual method to be implemented by derived classes
    virtual void paint(QPainter& painter, const QPoint& position) = 0;

    // Setters
    void setSize(int size) { brushSize = size; }
    void setColor(const QColor& color) { brushColor = color; }

    // Getters
    int getSize() const { return brushSize; }
    QColor getColor() const { return brushColor; }

protected:
    int brushSize;
    QColor brushColor;
};

#endif // BRUSH_H
