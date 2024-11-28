#include "eraser.h"
#include <QPainter>

// Constructor
Eraser::Eraser():eraserSize(10){
    pen.setWidth(eraserSize);
    pen.setColor(Qt::transparent);
}

// Deconstructor
Eraser::~Eraser(){}


// void Eraser::mousePressEvent(QMouseEvent* event, QPainter* painter){

// }

// void Eraser::mouseMoveEvent(QMouseEvent* event, QPainter* painter) {

// }
// void Eraser::mouseReleaseEvent(QMouseEvent* event, QPainter* painter) {

// }


void Eraser::setBrushSize(int size) {
    eraserSize=size;
    pen.setWidth(eraserSize);
}

void Eraser::setColor(const QColor& color) {
    pen.setColor(color);
}
