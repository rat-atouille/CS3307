// brushtool.h
#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include <QColor>
#include <QPainter>
#include <memory>

class BrushTool {
public:
    enum BrushType {
        PEN,
        ERASER,
        BRUSH
    };

    virtual void draw(QPainter& painter, const QPointF& point) = 0;
    virtual void setColor(const QColor& color) = 0;
    virtual void setSize(int size) = 0;
    virtual ~BrushTool() = default;

    // Factory Method
    static std::unique_ptr<BrushTool> createBrush(BrushType type);
};

class PenBrush : public BrushTool {
public:
    void draw(QPainter& painter, const QPointF& point) override;
    void setColor(const QColor& color) override;
    void setSize(int size) override;

private:
    QColor m_color{Qt::black};
    int m_size{2};
};

class EraserBrush : public BrushTool {
public:
    void draw(QPainter& painter, const QPointF& point) override;
    void setColor(const QColor& color) override;
    void setSize(int size) override;

private:
    int m_size{10};
};

#endif // BRUSHTOOL_H
