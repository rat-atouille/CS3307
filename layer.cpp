#include "layer.h"
#include <algorithm>

Layer::Layer(const QString& name, int width, int height, int opacity)
    : name(name),
    image(width, height, QImage::Format_ARGB32_Premultiplied),
    opacity(std::clamp(opacity, 0, 100)),
    visible(true) {
    image.fill(Qt::transparent);
}

Layer::~Layer() = default;

void Layer::draw(QPainter& painter) {
    if (!visible) return;

    painter.setOpacity(static_cast<qreal>(opacity) / 100.0);
    painter.drawImage(0, 0, image);
}

void Layer::setOpacity(int newOpacity) {
    opacity = std::clamp(newOpacity, 0, 100);
}

int Layer::getOpacity() const {
    return opacity;
}

void Layer::setVisibility(bool isVisible) {
    visible = isVisible;
}

bool Layer::isVisible() const {
    return visible;
}

QString Layer::getName() const {
    return name;
}

QImage& Layer::getImage() {
    return image;
}

const QImage& Layer::getImage() const {
    return image;
}
