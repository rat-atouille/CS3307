#ifndef DRAWING_TOOLS_H
#define DRAWING_TOOLS_H

#include <QPainter>
#include <memory>

/**
 * @brief The DrawingTool class
 * Abstract Base Class for Drawing Tools
 */
class DrawingTool {
public:
    virtual void draw(QPainter& painter, const QPoint& start, const QPoint& end) = 0;
    virtual ~DrawingTool() = default;
};

// Concrete Drawing Tools
class PenTool : public DrawingTool {
public:
    void draw(QPainter& painter, const QPoint& start, const QPoint& end) override;
};

class EraserTool : public DrawingTool {
public:
    void draw(QPainter& painter, const QPoint& start, const QPoint& end) override;
};

class FillBucketTool : public DrawingTool {
public:
    void draw(QPainter& painter, const QPoint& start, const QPoint& end) override;
    void floodFill(QImage& image, const QPoint& pos, const QColor& targetColor, const QColor& replacementColor);
};

/**
 * @brief The DrawingToolFactory class
 * factory pattern for tools
 */
class DrawingToolFactory {
public:
    enum ToolType { Pen, Eraser, FillBucket };

    static std::unique_ptr<DrawingTool> createTool(ToolType type);

};

#endif // DRAWING_TOOLS_H
