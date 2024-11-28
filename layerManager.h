#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "layer.h"
#include "layerGroup.h"

class LayerManager {
public:
    // Singleton pattern
    static LayerManager& getInstance();

    void addLayer(std::unique_ptr<LayerComponent> layer);
    void addLayerGroup(std::unique_ptr<LayerGroup> group);
    void removeLayer(LayerComponent* layer);
    void moveLayer(int fromIndex, int toIndex);

    void mergeLayers(LayerComponent* sourceLayer, LayerComponent* targetLayer);

    LayerComponent* getLayer(int index);

    // Iteration
    auto begin() { return layers.begin(); }
    auto end() { return layers.end(); }
    auto begin() const { return layers.cbegin(); }
    auto end() const { return layers.cend(); }

    // Bulk Operations
    void setAllLayersOpacity(int opacity);
    void toggleAllLayersVisibility();

    int layerCount() const;
    bool isEmpty() const;
    void clear();

private:
    LayerManager() = default;
    ~LayerManager() = default;

    LayerManager(const LayerManager&) = delete;
    LayerManager& operator=(const LayerManager&) = delete;

    std::vector<std::unique_ptr<LayerComponent>> layers;
};

#endif // LAYERMANAGER_H
