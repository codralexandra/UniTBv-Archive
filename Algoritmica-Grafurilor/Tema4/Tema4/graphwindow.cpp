#include "graphwindow.h"
#include <qdebug.h>

GraphWindow::GraphWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GraphWindow::~GraphWindow()
{}

void GraphWindow::setNodes(std::vector<Node*> nodes)
{
	m_nodes = nodes;
}

void GraphWindow::setArches(std::vector<Arch> arches)
{
	qDebug() << "Setting arches. Size before: " << m_arches.size();
	m_arches.clear();
	m_arches = arches;
	qDebug() << "Arches set. Size now: " << m_arches.size();
}

void GraphWindow::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);
	// Clear the entire widget
	painter.eraseRect(rect());

	uint32_t nodeRadius = 40;
	uint32_t nodeBorderWidth = 3;
	uint32_t lineWidth = 3;

	//DRAW ARCHES
	for (const Arch& arch : m_arches)
	{
		QPen pen(Qt::black);
		pen.setWidth(lineWidth);
		painter.setPen(pen);
		int circle1X = arch.getFirstNode().getPosition().x();
		int circle1Y = arch.getFirstNode().getPosition().y();
		int circle2X = arch.getSecondNode().getPosition().x();
		int circle2Y = arch.getSecondNode().getPosition().y();

		double angle = std::atan2(circle2Y - circle1Y, circle2X - circle1X);

		int lineStartX = circle1X + static_cast<int>(10 * std::cos(angle));
		int lineStartY = circle1Y + static_cast<int>(10 * std::sin(angle));

		int lineEndX = circle2X - static_cast<int>(10 * std::cos(angle));
		int lineEndY = circle2Y - static_cast<int>(10 * std::sin(angle));

		painter.drawLine(lineStartX, lineStartY, lineEndX, lineEndY);
	}
	//DRAW NODES
	for (Node* node : m_nodes)
	{
		QRect circle(node->getPosition().x() - nodeRadius / 2, node->getPosition().y() - nodeRadius / 2, nodeRadius, nodeRadius);
		QPen pen(Qt::black);
		pen.setWidth(nodeBorderWidth);
		painter.setPen(pen);
		QBrush brush(Qt::lightGray);
		painter.setBrush(brush);
		painter.drawEllipse(circle);

		QString nodeValue;
		nodeValue.setNum(node->getValue());
		painter.drawText(circle, Qt::AlignCenter, nodeValue);
	}
}
