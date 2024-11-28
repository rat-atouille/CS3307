#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include "layerComponent.h"
#include <vector>
#include <memory>

class LayerGroup : public LayerComponent {
public:
    explicit LayerGroup(const QString& name);
    ~LayerGroup() override;

    void addLayer(std::unique_ptr<LayerComponent> layer);
    void removeLayer(LayerComponent* layer);

    void draw(QPainter& painter) override;
    void setOpacity(int opacity) override;
    int getOpacity() const override;

    void setVisibility(bool visible) override;
    bool isVisible() const override;

    QString getName() const override;

private:
    QString name;
    int opacity;
    bool visible;

    std::vector<std::unique_ptr<LayerComponent>> layers;
};

#endif // LAYERGROUP_H
