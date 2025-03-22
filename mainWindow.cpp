#include "mainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Grid.h"


MainWindow::MainWindow(QMainWindow* parent) : QMainWindow(parent){

	setWindowTitle("Jeu de la Vie");
	setMinimumWidth(1024);
	setMinimumHeight(816);

	scene = new QGraphicsScene(this);
	view = new QGraphicsView(scene);
	view->setRenderHint(QPainter::Antialiasing);

	int gridSize = 150;
	int cellSize = 5;
	int totalSize = gridSize * cellSize;
	int margin = 50;

	view->setSceneRect(-totalSize/2 - margin, -totalSize/2 - margin, totalSize + 2*margin, totalSize + 4*margin);

	scene->setBackgroundBrush(QBrush(Qt::black));
	view->setBackgroundBrush(QBrush(Qt::black));


	grid = new Grid(scene, gridSize, gridSize);

	view->centerOn(0, 0);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


	startBtn = new QPushButton("Start", this);
	stopBtn = new QPushButton("Stop", this);
	speedSliderLabel = new QLabel("x1", this);
	speedSlider = new QSlider(Qt::Horizontal, this);
	speedSlider->setFixedWidth(200);
	speedSlider->setRange(1, 10);


	QWidget* buttonWidget = new QWidget(this);
	QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
	buttonLayout->setContentsMargins(10, 5, 10, 5);
	buttonLayout->addWidget(startBtn);
	buttonLayout->addWidget(stopBtn);
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(speedSlider);
	buttonLayout->addWidget(speedSliderLabel);


	QWidget* centralWidget = new QWidget(this);
	QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
	mainLayout->setSpacing(5);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addWidget(view);
	mainLayout->addWidget(buttonWidget);
	setCentralWidget(centralWidget);
	
	
	connect(speedSlider, &QSlider::valueChanged, grid, &Grid::setSpeed);
	connect(startBtn, &QPushButton::clicked, grid, &Grid::startGame);
	connect(stopBtn, &QPushButton::clicked, grid, &Grid::stopGame);
	connect(speedSlider, &QSlider::valueChanged, this, [this](int value){
		speedSliderLabel->setText("x" + QString::number(value));
	});


	stopBtn->setEnabled(false);
	connect(startBtn, &QPushButton::clicked, [this](){
		startBtn->setEnabled(false);
		stopBtn->setEnabled(true);
	});
	connect(stopBtn, &QPushButton::clicked, [this](){
		startBtn->setEnabled(true);
		stopBtn->setEnabled(false);
	});
	
}
