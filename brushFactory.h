#ifndef BRUSHFACTORY_H
#define BRUSHFACTORY_H

#include "pen.h"
#include "eraser.h"
#include <memory>

enum class BrushType {
    Pen,
    Eraser
};

class BrushFactory {
public:
    static std::unique_ptr<Brush> createBrush(BrushType type, int size, const QColor& color = Qt::black) {
        if (type == BrushType::Pen) {
            return std::make_unique<Pen>(size, color);
        } else if (type == BrushType::Eraser) {
            return std::make_unique<Eraser>(size);
        }
        return nullptr; // Return nullptr if the type is not recognized
    }
};

#endif // BRUSHFACTORY_H
