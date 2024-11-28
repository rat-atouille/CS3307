#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>
#include <QPainter>
#include "layerManager.h"

class Project : public QWidget {
    Q_OBJECT

public:
    explicit Project(LayerManager* manager, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    LayerManager* layerManager;
};

#endif // PROJECT_H
