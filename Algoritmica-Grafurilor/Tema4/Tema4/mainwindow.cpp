#include "mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_selectedNodeForArc = nullptr;
	m_draggedNode = nullptr;
	m_nodeDragState = false;

	connect(ui.kruskalButton, &QPushButton::clicked, this, &MainWindow::on_kruskalButton_clicked);

	graphWindow = new GraphWindow;
}

MainWindow::~MainWindow()
{
	delete graphWindow;
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_nodeDragState) {
		m_nodeDragState = false;
		m_draggedNode = nullptr;
	}
	if (event->button() == Qt::LeftButton)
	{
		//ADD NODE
		bool overlapping = false;
		for (Node* node : m_graph.getNodes())
		{
			Node tempNode;
			tempNode.setPosition(event->pos());
			tempNode.setValue(20);

			if (node->isOverlapping(tempNode))
			{
				overlapping = true;
				break;
			}
		}

		if (!overlapping)
		{
			QPoint position = event->pos();
			Node* newNode = new Node;
			newNode->setPosition(position);
			newNode->setValue(m_graph.getNodes().size() + 1);
			m_graph.addNode(newNode);
			update();
		}
	}
	else if (event->button() == Qt::RightButton)
	{
		//ADD ARCH BETWEEN NODES
		QPoint position = event->pos();
		Node* clickedNode = m_graph.getNodeAtPosition(position);

		if (clickedNode)
		{
			if (!m_selectedNodeForArc)
			{
				m_selectedNodeForArc = clickedNode;
			}
			else
			{
				Node* secondNode = clickedNode;
				if (m_selectedNodeForArc != secondNode)
				{
					Arch* newArch = new Arch(m_selectedNodeForArc, secondNode,0);
					uint32_t archCost = openTextBox();
					newArch->setCost(archCost);
					m_graph.addArch(newArch);
					update();
				}
				m_selectedNodeForArc = nullptr;
			}
		}
		update();
	}
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		std::vector<Node*> nodes = m_graph.getNodes();

		for (Node* node : nodes) {
			if (abs(event->pos().x() - node->getPosition().x()) < 10 && abs(event->pos().y() - node->getPosition().y()) < 10) {
				m_nodeDragState = true;
				m_draggedNode = node;
				m_lastMousePos = event->pos();
				break;
			}
		}
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (m_nodeDragState) {
		int dx = event->pos().x() - m_lastMousePos.x();
		int dy = event->pos().y() - m_lastMousePos.y();

		m_draggedNode->setPosition(m_draggedNode->getPosition() + QPoint(dx, dy));
		m_lastMousePos = event->pos();
		update();
	}
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QMainWindow::paintEvent(event);

	QPainter painter(this);
	uint32_t nodeRadius = 40;
	uint32_t nodeBorderWidth = 3;
	uint32_t lineWidth = 3;

	//DRAW ARCHES
	for (Arch* arch : m_graph.getArches())
	{
		QPen pen(Qt::black);
		pen.setWidth(lineWidth);
		painter.setPen(pen);
		int circle1X = arch->getFirstNode().getPosition().x();
		int circle1Y = arch->getFirstNode().getPosition().y();
		int circle2X = arch->getSecondNode().getPosition().x();
		int circle2Y = arch->getSecondNode().getPosition().y();

		double angle = std::atan2(circle2Y - circle1Y, circle2X - circle1X);

		int lineStartX = circle1X + static_cast<int>(10 * std::cos(angle));
		int lineStartY = circle1Y + static_cast<int>(10 * std::sin(angle));

		int lineEndX = circle2X - static_cast<int>(10 * std::cos(angle));
		int lineEndY = circle2Y - static_cast<int>(10 * std::sin(angle));

		painter.drawLine(lineStartX, lineStartY, lineEndX, lineEndY);
		
		QPen redPen(Qt::red);
		painter.setPen(redPen);

		int textX = (lineStartX + lineEndX) / 2;
		int textY = (lineStartY + lineEndY) / 2;

		QString costText = QString::number(arch->getCost());

		textX += 5;
		textY -= 5;

		painter.drawText(textX, textY, costText);
	}
	//DRAW NODES
	for (Node* node : m_graph.getNodes())
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
	//DRAW SELECTION
	if (m_selectedNodeForArc && m_selectedNodeForArc->getValue() > 0) {
		QRect circle(m_selectedNodeForArc->getPosition().x() - nodeRadius / 2, m_selectedNodeForArc->getPosition().y() - nodeRadius / 2, nodeRadius, nodeRadius);
		QPen pen(Qt::blue);
		pen.setWidth(nodeBorderWidth);
		painter.setPen(pen);
		QBrush brush(Qt::transparent);
		painter.setBrush(brush);
		painter.drawEllipse(circle);
	}
}

uint32_t MainWindow::openTextBox()
{
	costBox inputDialog(this);
	if (inputDialog.exec() == QDialog::Accepted)
	{
		return inputDialog.getCost();
	}
	else
	{
		return 0;
	}
}

void MainWindow::drawHighlightedEdges(QPainter& painter, const std::vector<Arch>& arches)
{
	for (const Arch& highlightedArch : arches)
	{
		QPoint firstNodePos = highlightedArch.getFirstNode().getPosition();
		QPoint secondNodePos = highlightedArch.getSecondNode().getPosition();
		painter.drawLine(firstNodePos, secondNodePos);
	}
}

void MainWindow::on_kruskalButton_clicked()
{
	highlightedArches.clear();
	m_graph.kruskalAlgorithm();

	highlightedArches = m_graph.getMinArches();

	graphWindow->show();
	graphWindow->setNodes(m_graph.getNodes());
	graphWindow->setArches(highlightedArches);
	update();
}

void MainWindow::on_primButton_clicked()
{
	qDebug() << "Button clicked. Size before primAlgorithm: " << highlightedArches.size();
	highlightedArches.clear();
	m_graph.primAlgorithm();

	highlightedArches = m_graph.getMinArches();

	qDebug() << "Size after primAlgorithm: " << highlightedArches.size();

	graphWindow->show();
	graphWindow->setNodes(m_graph.getNodes());
	graphWindow->setArches(highlightedArches);

	qDebug() << "Calling repaint";
	graphWindow->repaint();  // Use repaint() directly
	QCoreApplication::processEvents();  // Process events before continuing
}