#pragma once

#include <QWidget>
#include "ui_graphwindow.h"
#include "node.h"
#include "arch.h"
#include <QPainter>

class GraphWindow : public QWidget
{
	Q_OBJECT

public:
	GraphWindow(QWidget *parent = nullptr);
	~GraphWindow();
	void setNodes(std::vector<Node*> nodes);
	void setArches(std::vector<Arch> arches);
	void paintEvent(QPaintEvent* event);

private:
	Ui::GraphWindowClass ui;
	std::vector<Node*> m_nodes;
	std::vector<Arch> m_arches;
};
