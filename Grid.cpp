#include "Grid.h"

Grid::Grid(QGraphicsScene* scene_v, int rows_v, int cols_v) : scene{scene_v}, rows{rows_v}, cols{cols_v}{

	if (!scene) {
		throw std::runtime_error("Scene cannot be null");
	}
	if (rows <= 0 || cols <= 0){
		throw std::runtime_error("Grid dimensions must be positive");
	}
    
	timer = new QTimer(this);
	initGrid();
	connect(timer, &QTimer::timeout, this, &Grid::updateGrid);
	
}

Grid::~Grid(){
	clearGrid();
}

void Grid::initGrid(){

	if (!scene) return;
    
	int totalWidth = cols * cellSize;
	int totalHeight = rows * cellSize;
	int startX = -totalWidth / 2;
	int startY = -totalHeight / 2;
    
	grid.clear();
	grid.resize(rows);
    
	try{
		for(int i = 0; i < rows; i++){
			grid[i].resize(cols);
			for(int j = 0; j < cols; j++){
				Cell* cell = new Cell(startX + j*cellSize, startY + i*cellSize, cellSize);
				scene->addItem(cell);
				grid[i][j] = cell;
			}
		}
	}
	
	catch (...){
		clearGrid();
		throw;
	}
	
}

int Grid::countNeighbors(int row, int col){

	int count = 0;
	
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			if(i == 0 && j == 0) continue;
			if(isValidCell(row+i,col+j) && grid[row+i][col+j]->isAlive()) count++;
		}
	}
	
	return count;
}

bool Grid::isValidCell(int row, int col) const{
	return row >= 0 && row < rows && col >= 0 && col < cols;
}

void Grid::updateGrid(){

	std::vector<std::vector<bool>> nextGen(rows, std::vector<bool>(cols));
	
	for(int i = 0; i < rows ; i++){
		for(int j = 0; j < cols ; j++){
		
			int neighborsCount = countNeighbors(i,j);
			bool isCurrentlyAlive = grid[i][j]->isAlive();
			
			if(isCurrentlyAlive && (neighborsCount == 2 || neighborsCount == 3)){ /* Stay alive */
				nextGen[i][j] = true;
			}
			
			else if(!isCurrentlyAlive && neighborsCount == 3){ /* Reproduction */
				nextGen[i][j] = true;
			}
			
			else { /* Overpopulation or underpopulation */
				nextGen[i][j] = false;
			}
			
		}
	}
	
	for(int i = 0; i < rows ; i++){
		for(int j = 0; j < cols ; j++){
			grid[i][j]->setAlive(nextGen[i][j]);
		}
	}
}

void Grid::startGame(){
	timer->start(speed);
}

void Grid::stopGame(){
	timer->stop();
}

void Grid::clearGrid(){

	for(auto &row : grid){
		for(auto &cell : row){
			scene->removeItem(cell);
			delete cell;
		}
	}
	
	grid.clear();
}


void Grid::setSpeed(int speed_v){

	speed = std::max(20, std::min(1000, 1000 - (speed_v * 190)));
	
	if (timer->isActive()){
		timer->start(speed);
	}
}


int Grid::getRows() const{
	return rows;
}

int Grid::getCols() const{
	return cols;
}

int Grid::getCellSize() const{
	return cellSize;
}

int Grid::getspeed() const{
	return speed;
}

