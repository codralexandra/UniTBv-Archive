#pragma once

#include <qwidget.h>
#include "ui_QtLabirynth.h"
#include <qhboxlayout>
#include <qpushbutton.h>
#include <qvboxlayout>
#include <qlabel.h>
#include <iostream>
#include <qgridlayout.h>
#include <QRect>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "Graph.h"


class QtLabirynth : public QWidget
{
public:
	QtLabirynth(QWidget* parent = Q_NULLPTR);
	~QtLabirynth();
public slots:
	void pushExitButton();
	void pushGenerateButton();
	void pushGenerateGraphButton();
	void pushBackButton();
	void pushGenerateSolutionButton();
private:
	QWidget* graphWindow;
	QWidget* solutionWindow;

	QHBoxLayout* mainLayout;
	QVBoxLayout* buttonLayout;
	QGridLayout* labirynthLayout;
	QVBoxLayout* solutionLayout;

	QPushButton* exitButton;
	QPushButton* generateButton;
	QPushButton* generateGraphButton;
	QPushButton* backButton;
	QPushButton* generateLabyrinthSolution;
	
	Graph graph;
};
