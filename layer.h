#ifndef LAYER_H
#define LAYER_H

#include <QImage>
#include <QString>
#include <QPainter>
#include "layerComponent.h"

class Layer : public LayerComponent {
public:
    explicit Layer(const QString& name, int width, int height, int opacity = 100);
    ~Layer() override;

    void draw(QPainter& painter) override;
    void setOpacity(int opacity) override;
    int getOpacity() const override;
    void setVisibility(bool visible) override;
    bool isVisible() const override;
    QString getName() const override;

    QImage& getImage();              // Editable image reference
    const QImage& getImage() const;  // Read-only image reference

private:
    QString name;
    QImage image;
    int opacity;
    bool visible;
};

#endif // LAYER_H
