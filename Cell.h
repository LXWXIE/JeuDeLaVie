
#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <QBrush>

class Cell : public QGraphicsRectItem{

	public:
		explicit Cell(int x, int y, int cellSize);
		virtual ~Cell(){};
		void setAlive(bool alive);
		bool isAlive();
		virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
		
	private:
		bool state;
};

#endif

