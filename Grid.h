#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "Cell.h"
#include <vector>

class Grid : public QObject{
	Q_OBJECT
	public:
		explicit Grid(QGraphicsScene* scene_v, int rows_v, int cols_v);
		virtual ~Grid();
		void initGrid();
		void updateGrid();
		void clearGrid();
		void setCellSize(int size);
		int getRows() const;
		int getCols() const;
		int getCellSize() const;
		int getspeed() const;

	public slots:
		void startGame();
		void stopGame();
		void setSpeed(int speed);

	private:
		int countNeighbors(int row, int col);
		bool isValidCell(int row, int col) const;

		QGraphicsScene* scene;
		std::vector<std::vector<Cell*>> grid;
		int rows;
		int cols;
		int cellSize {5};
		QTimer *timer;
		int speed{1000};
};

#endif

