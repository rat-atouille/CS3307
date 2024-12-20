
#ifndef LAYERED_CANVAS_H
#define LAYERED_CANVAS_H

#include <QWidget>
#include <QVector>
#include "Layer.h"
#include "DrawingTools.h"

// logic for rendering, drawing, reordering, updating the layer
class LayeredCanvas : public QWidget {
    Q_OBJECT

public:
    LayeredCanvas(QWidget* parent = nullptr);

    void addNewLayer(const QString& name = QString());
    void deleteCurrentLayer();
    void toggleLayerVisibility(int index);

    // setters
    void setCurrentLayer(int index);
    void setTool(DrawingToolFactory::ToolType type);
    void setPenColor(const QColor& color);
    void setPenWidth(int width);
    void renameLayer(int index, const QString& newName);

    // Save and Load methods
    bool saveProject(const QString& fileName);
    bool loadProject(const QString& fileName);
    bool exportImage(const QString& fileName, const QString& format);

    void moveLayer(int fromIndex, int toIndex);
    void resizeCanvas(const QSize& newSize);
    QSize getCanvasSize() const { return size(); }

    // Getter for layers to allow access in LayerManagerDialog
    const QVector<Layer>& getLayers() const { return layers; }
    // getter
    const QVector<QString>& getLayerNames() const { return layerNames; }
    int getPenWidth() const { return penWidth; }

signals:
    void layersChanged();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QSize canvasSize;
    QVector<Layer> layers;
    QVector<QString> layerNames;
    int currentLayerIndex;
    QPoint lastPoint;
    bool isDrawing;
    QColor currentColor;
    int penWidth;
    std::unique_ptr<DrawingTool> currentTool;
};

#endif // LAYERED_CANVAS_H


