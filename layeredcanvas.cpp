#include "LayeredCanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDataStream>
#include <QBuffer>

// logic for rendering, drawing, reordering, updating the layer

// Constructor for LayeredCanvas
LayeredCanvas::LayeredCanvas(QWidget* parent)
    : QWidget(parent),
    currentLayerIndex(0),
    isDrawing(false),
    currentColor(Qt::black),  // Default pen color
    penWidth(3) {            // Default pen width
    setMouseTracking(true);    // Enable mouse tracking for better interactivity

    // Add an initial layer
    layers.push_back(Layer(LayerBuilder().build()));
    layerNames.push_back("Layer 1");

    // Set default tool to Pen
    currentTool = DrawingToolFactory::createTool(DrawingToolFactory::Pen);
}

// Add a new layer with an optional name
void LayeredCanvas::addNewLayer(const QString& name) {
    layers.push_back(Layer(LayerBuilder().build()));

    // Assign a default name if none is provided
    if (name.isEmpty()) {
        layerNames.push_back(QString("Layer %1").arg(layers.size()));
    } else {
        layerNames.push_back(name);
    }

    currentLayerIndex = layers.size() - 1; // Set the new layer as active
    emit layersChanged();                 // Notify listeners
}

// Rename an existing layer
void LayeredCanvas::renameLayer(int index, const QString& newName) {
    if (index >= 0 && index < layerNames.size()) {
        layerNames[index] = newName;
        emit layersChanged();
    }
}

// Save the project to a JSON file
bool LayeredCanvas::saveProject(const QString& fileName) {
    QJsonObject projectJson;
    QJsonArray layersArray;

    for (int i = 0; i < layers.size(); ++i) {
        QJsonObject layerObj;

        // Serialize the layer image to base64
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        layers[i].image.save(&buffer, "PNG");

        layerObj["name"] = layerNames[i];
        layerObj["image"] = QString(imageData.toBase64());
        layerObj["visible"] = layers[i].visible;
        layerObj["opacity"] = layers[i].opacity;

        layersArray.append(layerObj);
    }

    projectJson["layers"] = layersArray;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(projectJson);
        file.write(doc.toJson());
        file.close();
        return true;
    }
    return false;
}

// Load a project from a JSON file
bool LayeredCanvas::loadProject(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject projectJson = doc.object();
    QJsonArray layersArray = projectJson["layers"].toArray();

    // Clear current layers and names
    layers.clear();
    layerNames.clear();

    // Recreate layers from JSON
    for (const QJsonValue& layerValue : layersArray) {
        QJsonObject layerObj = layerValue.toObject();

        // Decode the image from base64
        QByteArray imageData = QByteArray::fromBase64(layerObj["image"].toString().toUtf8());
        QImage layerImage;
        layerImage.loadFromData(imageData, "PNG");

        Layer layer(layerImage,
                    layerObj["visible"].toBool(true),
                    layerObj["opacity"].toDouble(1.0));

        layers.push_back(layer);
        layerNames.push_back(layerObj["name"].toString());
    }

    currentLayerIndex = 0; // Set the first layer as active
    emit layersChanged();
    update();
    return true;
}

// Export the canvas as a flattened image
bool LayeredCanvas::exportImage(const QString& fileName, const QString& format) {
    QImage finalImage(size(), QImage::Format_ARGB32_Premultiplied);
    finalImage.fill(Qt::white);

    QPainter painter(&finalImage);
    for (const auto& layer : layers) {
        if (layer.visible) {
            painter.setOpacity(layer.opacity);
            painter.drawImage(0, 0, layer.image);
        }
    }
    return finalImage.save(fileName, format.toUtf8().constData());
}

// Delete the currently active layer
void LayeredCanvas::deleteCurrentLayer() {
    if (layers.size() > 1) {
        layers.removeAt(currentLayerIndex);
        layerNames.removeAt(currentLayerIndex);
        currentLayerIndex = qMin(currentLayerIndex, layers.size() - 1); // Adjust the active layer index
        emit layersChanged();
        update();
    }
}

// Toggle the visibility of a layer
void LayeredCanvas::toggleLayerVisibility(int index) {
    layers[index].visible = !layers[index].visible;
    update();
}

// Set the currently active layer
void LayeredCanvas::setCurrentLayer(int index) {
    if (index >= 0 && index < layers.size()) {
        currentLayerIndex = index;
    }
}

// Set the current drawing tool
void LayeredCanvas::setTool(DrawingToolFactory::ToolType type) {
    currentTool = DrawingToolFactory::createTool(type);
}

// Set the pen color
void LayeredCanvas::setPenColor(const QColor& color) {
    currentColor = color;
}

// Set the pen width
void LayeredCanvas::setPenWidth(int width) {
    penWidth = width;
}

// Handle mouse press events for drawing or filling
void LayeredCanvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (!layers[currentLayerIndex].visible) {
            return; // Prevent drawing on hidden layers
        }
        lastPoint = event->pos();
        isDrawing = true;

        if (auto* fillTool = dynamic_cast<FillBucketTool*>(currentTool.get())) {
            QPainter painter(&layers[currentLayerIndex].image);
            painter.setPen(QPen(currentColor, penWidth, Qt::SolidLine, Qt::RoundCap));
            fillTool->draw(painter, event->pos(), event->pos());
            update();
        }
    }
}

// Handle mouse move events for drawing
void LayeredCanvas::mouseMoveEvent(QMouseEvent* event) {
    if ((event->buttons() & Qt::LeftButton) && isDrawing) {
        if (!layers[currentLayerIndex].visible) {
            return; // Prevent drawing on hidden layers
        }

        if (dynamic_cast<FillBucketTool*>(currentTool.get())) {
            return; // Skip processing for fill tool
        }

        QPainter painter(&layers[currentLayerIndex].image);
        painter.setPen(QPen(currentColor, penWidth, Qt::SolidLine, Qt::RoundCap));
        currentTool->draw(painter, lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

// Handle mouse release events
void LayeredCanvas::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = false;
    }
}

// Paint all visible layers onto the canvas
void LayeredCanvas::paintEvent(QPaintEvent*) {
    QPainter canvasPainter(this);
    canvasPainter.fillRect(rect(), Qt::white); // Fill with a white background

    for (int i = layers.size() - 1; i >= 0; --i) { // Draw from bottom to top
        if (layers[i].visible) {
            canvasPainter.setOpacity(layers[i].opacity);
            canvasPainter.drawImage(0, 0, layers[i].image);
        }
    }
}

// Move a layer from one index to another
void LayeredCanvas::moveLayer(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < layers.size() &&
        toIndex >= 0 && toIndex < layers.size() && fromIndex != toIndex) {
        layers.move(fromIndex, toIndex);
        layerNames.move(fromIndex, toIndex);
        currentLayerIndex = toIndex; // Update the active layer
        emit layersChanged();
        update();
    }
}

// Resize the canvas and adjust all layers
void LayeredCanvas::resizeCanvas(const QSize& newSize) {
    for (Layer& layer : layers) {
        QImage newImage(newSize, QImage::Format_ARGB32_Premultiplied);
        newImage.fill(Qt::transparent); // Preserve transparency

        QPainter painter(&newImage);
        painter.drawImage(0, 0, layer.image);
        layer.image = newImage;
    }

    canvasSize = newSize;
    setMinimumSize(newSize);
    resize(newSize);
    update();
}
