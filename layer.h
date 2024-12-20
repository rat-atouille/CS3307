#ifndef LAYER_H
#define LAYER_H

#include <QImage>
#include <QVector>

/**
 * @brief The Layer class
 * Represents a single layer in the canvas.
 */

class Layer {
public:
    Layer(const QImage& img, bool vis = true, qreal op = 1.0);

    QImage image;   // drawing area
    bool visible;
    qreal opacity;
};

class LayerBuilder {
public:
    LayerBuilder();

    LayerBuilder& setVisibility(bool visible);
    LayerBuilder& setOpacity(qreal opacity);
    QImage build();

private:
    QImage image;
    bool visible;
    qreal opacity;
};

#endif // LAYER_H
