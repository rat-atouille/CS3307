// canvas.h
#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include "layer.h"
#include "brushtool.h"
#include "observerinterface.h"

class Canvas : public QWidget, public LayerObserver {
    Q_OBJECT

public:
    explicit Canvas(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void setBrushTool(BrushTool::BrushType type);

    // Observer method
    void onLayerChanged() override;

private:
    std::unique_ptr<BrushTool> m_currentBrush;
    QPointF m_lastPos;
};

#endif // CANVAS_H
