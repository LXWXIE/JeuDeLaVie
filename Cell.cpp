#include "Cell.h"
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QColor>

Cell::Cell(int x, int y, int cellSize) : QGraphicsRectItem(x, y, cellSize, cellSize) {
	state = false;
	setBrush(QBrush(Qt::black));

	QPen gridPen(QColor(20, 20, 20));
	gridPen.setWidth(1);
	setPen(gridPen);
}

void Cell::setAlive(bool alive){
	state = alive;
	if (state == true){
		setBrush(QBrush(Qt::white));
	}
	else{
		setBrush(QBrush(Qt::black));
	}
	QPen currentPen = pen();
	setPen(currentPen);
}

bool Cell::isAlive() {
	return state;
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent* event){
	setAlive(!isAlive());
}
