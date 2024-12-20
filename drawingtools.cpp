#include "DrawingTools.h"
#include <QStack>
#include <QPainterPath>

// Implementation of the PenTool's draw function.
// Draws a straight line between the start and end points using the painter.
void PenTool::draw(QPainter& painter, const QPoint& start, const QPoint& end) {
    painter.drawLine(start, end);
}

// Implementation of the EraserTool's draw function.
// Erases pixels by making them transparent along the line from start to end.
void EraserTool::draw(QPainter& painter, const QPoint& start, const QPoint& end) {
    // Get the QImage from the painter's device
    QImage* image = reinterpret_cast<QImage*>(painter.device());
    if (!image) return;

    painter.save(); // Save the current state of the painter

    // Create a path for the line to erase
    QPainterPath path;
    path.moveTo(start);
    path.lineTo(end);

    // Set up the eraser pen with a transparent color
    QPen eraserPen = painter.pen();
    eraserPen.setColor(Qt::transparent);
    eraserPen.setWidth(eraserPen.width() * 2);  // Double the width of the pen for erasing
    eraserPen.setCapStyle(Qt::RoundCap); // Use rounded edges for smoother erasing
    painter.setPen(eraserPen);

    // Set composition mode to clear pixels (make them transparent)
    painter.setCompositionMode(QPainter::CompositionMode_Clear);

    // Draw the eraser stroke using the defined path
    painter.strokePath(path, eraserPen);

    // Restore the painter's state to its original settings
    painter.restore();
}

// Implementation of the FillBucketTool's draw function.
// Fills an area starting at the 'start' point with the painter's current color.
void FillBucketTool::draw(QPainter& painter, const QPoint& start, const QPoint& end) {
    Q_UNUSED(end); // Ignore the 'end' parameter since it's not needed for the fill operation

    // Get the QImage from the painter's device
    QImage& image = *reinterpret_cast<QImage*>(painter.device());

    // Determine the target color to replace and the new fill color
    QColor targetColor = image.pixelColor(start);
    QColor fillColor = painter.pen().color();

    // Perform the fill operation only if the target color differs from the fill color
    if (targetColor != fillColor) {
        floodFill(image, start, targetColor, fillColor);
    }
}

// Recursive flood fill algorithm to replace a target color with a new color.
void FillBucketTool::floodFill(QImage& image, const QPoint& pos, const QColor& targetColor, const QColor& replacementColor) {
    // Base case: check if the current position is out of bounds or already filled
    if (!image.rect().contains(pos) ||
        image.pixelColor(pos) != targetColor ||
        targetColor == replacementColor) {
        return;
    }

    // Use a stack to manage points to fill (iterative approach to avoid recursion depth limits)
    QStack<QPoint> stack;
    stack.push(pos);

    while (!stack.isEmpty()) {
        QPoint currentPos = stack.pop();

        // Skip if the current position is out of bounds or doesn't match the target color
        if (!image.rect().contains(currentPos) ||
            image.pixelColor(currentPos) != targetColor) {
            continue;
        }

        // Set the current pixel to the replacement color
        image.setPixelColor(currentPos, replacementColor);

        // Add neighboring pixels to the stack for further processing
        stack.push(currentPos + QPoint(0, 1));  // Down
        stack.push(currentPos + QPoint(0, -1)); // Up
        stack.push(currentPos + QPoint(1, 0));  // Right
        stack.push(currentPos + QPoint(-1, 0)); // Left
    }
}

// Factory method for creating instances of different drawing tools based on the ToolType.
std::unique_ptr<DrawingTool> DrawingToolFactory::createTool(ToolType type) {
    switch (type) {
    case Pen:
        return std::make_unique<PenTool>(); // Create and return a PenTool
    case Eraser:
        return std::make_unique<EraserTool>(); // Create and return an EraserTool
    case FillBucket:
        return std::make_unique<FillBucketTool>(); // Create and return a FillBucketTool
    default:
        return std::make_unique<PenTool>(); // Default to PenTool if the type is unrecognized
    }
}
