#include "layerGroup.h"
#include <algorithm>

LayerGroup::LayerGroup(const QString& name) : name(name), opacity(100), visible(true) {}

LayerGroup::~LayerGroup() = default;

void LayerGroup::addLayer(std::unique_ptr<LayerComponent> layer) {
    layers.push_back(std::move(layer));
}

void LayerGroup::removeLayer(LayerComponent* layer) {
    layers.erase(std::remove_if(layers.begin(), layers.end(),
                                [layer](const std::unique_ptr<LayerComponent>& item) { return item.get() == layer; }),
                 layers.end());
}

void LayerGroup::draw(QPainter& painter) {
    for (const auto& layer : layers) {
        layer->draw(painter);
    }
}

void LayerGroup::setOpacity(int newOpacity) {
    opacity = std::clamp(newOpacity, 0, 100);
    for (auto& layer : layers) {
        layer->setOpacity(opacity);
    }
}

int LayerGroup::getOpacity() const {
    return opacity;
}

void LayerGroup::setVisibility(bool isVisible) {
    visible = isVisible;
    for (auto& layer : layers) {
        layer->setVisibility(isVisible);
    }
}

bool LayerGroup::isVisible() const {
    return visible;
}

QString LayerGroup::getName() const {
    return name;
}
