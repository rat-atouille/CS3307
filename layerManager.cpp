#include "layerManager.h"

LayerManager& LayerManager::getInstance() {
    static LayerManager instance;
    return instance;
}

void LayerManager::addLayer(std::unique_ptr<LayerComponent> layer) {
    layers.push_back(std::move(layer));
}

void LayerManager::addLayerGroup(std::unique_ptr<LayerGroup> group) {
    layers.push_back(std::move(group));
}

void LayerManager::removeLayer(LayerComponent* layer) {
    layers.erase(std::remove_if(layers.begin(), layers.end(),
                                [layer](const auto& comp) { return comp.get() == layer; }),
                 layers.end());
}

void LayerManager::moveLayer(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= layers.size() || toIndex < 0 || toIndex >= layers.size()) {
        throw std::out_of_range("Layer index out of range");
    }
    if (fromIndex == toIndex) return;

    auto layer = std::move(layers[fromIndex]);
    layers.erase(layers.begin() + fromIndex);
    layers.insert(layers.begin() + toIndex, std::move(layer));
}

LayerComponent* LayerManager::getLayer(int index) {
    if (index < 0 || index >= layers.size()) {
        throw std::out_of_range("Layer index out of range");
    }
    return layers[index].get();
}

void LayerManager::mergeLayers(LayerComponent* sourceLayer, LayerComponent* targetLayer) {
    auto targetTypedLayer = dynamic_cast<Layer*>(targetLayer);
    auto sourceTypedLayer = dynamic_cast<Layer*>(sourceLayer);

    if (targetTypedLayer && sourceTypedLayer) {
        QPainter painter(&targetTypedLayer->getImage());
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(0, 0, sourceTypedLayer->getImage());
        removeLayer(sourceLayer);
    }
}

void LayerManager::setAllLayersOpacity(int opacity) {
    for (auto& layer : layers) {
        layer->setOpacity(opacity);
    }
}

void LayerManager::toggleAllLayersVisibility() {
    for (auto& layer : layers) {
        layer->setVisibility(!layer->isVisible());
    }
}

int LayerManager::layerCount() const {
    return layers.size();
}

bool LayerManager::isEmpty() const {
    return layers.empty();
}

void LayerManager::clear() {
    layers.clear();
}
