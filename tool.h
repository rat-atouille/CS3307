#ifndef TOOL_H
#define TOOL_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QColor>

class Tool{
public:
    virtual ~Tool(){}

    // virtual void mousePressEvent(QMouseEvent* event, QPainter* painter) = 0;
    // virtual void mouseMoveEvent(QMouseEvent* event, QPainter* painter) = 0;
    // virtual void mouseReleaseEvent(QMouseEvent* event, QPainter* painter) = 0;

    virtual void setBrushSize(int size) = 0;
    virtual void setColor(const QColor& color) = 0;
};

#endif // TOOL_H
