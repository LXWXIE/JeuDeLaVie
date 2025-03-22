#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSlider>
#include <QLabel>
#include <QEvent>
#include <QWheelEvent>
#include "Grid.h"

class MainWindow : public QMainWindow{
	Q_OBJECT
	public:
		explicit MainWindow(QMainWindow* parent = nullptr);
		virtual ~MainWindow(){};
		
	private:
		QGraphicsScene * scene;
		QGraphicsView* view;
		Grid* grid;
		QPushButton* startBtn;
		QPushButton* stopBtn;
		QLabel* speedSliderLabel;
		QSlider* speedSlider;

};


#endif
