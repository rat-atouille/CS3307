#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>

#include <QWidget>
#include <QPushButton>
#include <QComboBox>

#include "tool.h"
#include "brush.h"
#include "eraser.h"

// Provides UI for selecting tools and colors
class Toolbar: public QWidget{
    Q_OBJECT
public:
    Toolbar(QWidget* parent = nullptr);
    ~Toolbar();

    Tool* getActiveTool() const;

private slots:
    void onToolChanged(int index);

private:
    Tool* activeTool;
    Brush* brushTool;
    Eraser* eraserTool;
    QComboBox* toolComboBox;

};

#endif // TOOLBAR_H
