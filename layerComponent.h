#ifndef LAYERCOMPONENT_H
#define LAYERCOMPONENT_H

#include <QString>
#include <QPainter>

class LayerComponent {
public:
    virtual ~LayerComponent() = default;

    virtual void draw(QPainter& painter) = 0;
    virtual void setOpacity(int opacity) = 0;
    virtual int getOpacity() const = 0;

    virtual void setVisibility(bool visible) = 0;
    virtual bool isVisible() const = 0;

    virtual QString getName() const = 0;
};

#endif // LAYERCOMPONENT_H
