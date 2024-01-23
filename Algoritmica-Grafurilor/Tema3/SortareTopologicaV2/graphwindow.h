#pragma once

#include <QWidget>
#include "ui_graphwindow.h"
#include "node.h"
#include <QPainter>

class GraphWindow : public QWidget
{
	Q_OBJECT

public:
	GraphWindow(QWidget *parent = nullptr);
	~GraphWindow();
	void paintEvent(QPaintEvent* event);

public:
	void setMatrix(const std::vector<std::vector<bool>>& matrix);
	void setNodes(const std::vector<Node*>& nodes);

private:
	Ui::GraphWindowClass ui;
	std::vector<std::vector<bool>> m_adjacencyMatrix;
	std::vector<Node*> m_nodes;
};
