#include "Layer.h"

// layer constructor
Layer::Layer(const QImage& img, bool vis, qreal op)
    : image(img), visible(vis), opacity(op) {}

// layerbuilder constructor
LayerBuilder::LayerBuilder()
    : image(800, 600, QImage::Format_ARGB32_Premultiplied),
    visible(true),
    opacity(1.0) {
    image.fill(Qt::transparent);
}

// setter function for visiblity
LayerBuilder& LayerBuilder::setVisibility(bool vis) {
    visible = vis;
    return *this;
}

// setter for layer opacity
LayerBuilder& LayerBuilder::setOpacity(qreal op) {
    opacity = op;
    return *this;
}

// return QImage of layer
QImage LayerBuilder::build() {
    return image;
}
