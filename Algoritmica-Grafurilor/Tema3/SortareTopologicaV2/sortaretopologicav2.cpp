#include "sortaretopologicav2.h"
#include <QPainter>
#include <qfile.h>
#include <qmessagebox.h>
#include <qdebug.h>

SortareTopologicaV2::SortareTopologicaV2(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_selectedNodeForArc = nullptr;
	m_draggedNode = nullptr;
	m_nodeDragState = false;
	connect(ui.adjacencyMatrixButton, &QPushButton::clicked, this, &SortareTopologicaV2::on_adjacencyMatrixButton_clicked);
	connect(ui.checkCircuitsButton, &QPushButton::clicked, this, &SortareTopologicaV2::on_checkCircuitsButton_clicked);
	connect(ui.sortedButton, &QPushButton::clicked, this, &SortareTopologicaV2::on_sortedButton_clicked);
	connect(ui.treeCheckButton, &QPushButton::clicked, this, &SortareTopologicaV2::on_treeCheckButton_clicked);
	connect(ui.rootButton, &QPushButton::clicked, this, &SortareTopologicaV2::on_rootButton_clicked);
}

SortareTopologicaV2::~SortareTopologicaV2()
{}

void SortareTopologicaV2::mouseReleaseEvent(QMouseEvent* event)
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
					Arch* newArch = new Arch(m_selectedNodeForArc, secondNode);
					m_graph.addArch(newArch);
					update();
				}
				m_selectedNodeForArc = nullptr;
			}
		}
		update();
	}
}

void SortareTopologicaV2::mousePressEvent(QMouseEvent* event)
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

void SortareTopologicaV2::mouseMoveEvent(QMouseEvent* event)
{
	if (m_nodeDragState) {
		int dx = event->pos().x() - m_lastMousePos.x();
		int dy = event->pos().y() - m_lastMousePos.y();

		m_draggedNode->setPosition(m_draggedNode->getPosition() + QPoint(dx, dy));
		m_lastMousePos = event->pos();
		update();
	}
}

void SortareTopologicaV2::paintEvent(QPaintEvent* event)
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
	}
	//ARCHES WITH ARROWS -----> FIX ARROW POSITION
	if (m_graph.getType()) {
		for (Arch* arch : m_graph.getArches())
		{
			QPointF firstPos = arch->getFirstNode().getPosition();
			QPointF secondPos = arch->getSecondNode().getPosition();

			double angle = atan2(secondPos.y() - firstPos.y(), secondPos.x() - firstPos.x());

			double arrowLength = 6.0;

			QPointF arrowPointOnPerimeter1(secondPos.x() + nodeRadius * cos(angle),
				secondPos.y() + nodeRadius * sin(angle));

			QPointF arrowPointOnPerimeter2(secondPos.x() + nodeRadius * cos(angle + M_PI),
				secondPos.y() + nodeRadius * sin(angle + M_PI));

			double arrowAngle = M_PI / 6.0;

			QPointF arrowPoint1(arrowPointOnPerimeter2.x() - arrowLength * cos(angle + arrowAngle),
				arrowPointOnPerimeter2.y() - arrowLength * sin(angle + arrowAngle));

			QPointF arrowPoint2(arrowPointOnPerimeter2.x() - arrowLength * cos(angle - arrowAngle),
				arrowPointOnPerimeter2.y() - arrowLength * sin(angle - arrowAngle));

			painter.drawLine(arrowPointOnPerimeter2, arrowPoint1);
			painter.drawLine(arrowPointOnPerimeter2, arrowPoint2);
		}
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

void SortareTopologicaV2::on_adjacencyMatrixButton_clicked()
{
	matrixFile.open("adjacencyMatrix.txt");
	m_graph.writeToFile(matrixFile);
	matrixFile.close();
}

void SortareTopologicaV2::on_checkCircuitsButton_clicked()
{
	ui.hasCircuitsLabel->clear();
	ui.noCircuitsLabel->clear();
	Node* startNode = m_graph.getNodes()[0];
	std::vector<Node*> result = m_graph.depthFirstTraversal(startNode);

	depthFirstFile.open("depthFirst.txt");
	for (uint32_t index = 0; index < result.size(); index++)
	{
		depthFirstFile << result[index]->getValue() << " ";
	}
	depthFirstFile.close();

	bool hasCircuit = m_graph.getCircuitStatus();

	if (hasCircuit == true)
		ui.hasCircuitsLabel->setText("Graph has circuits.");
	else ui.noCircuitsLabel->setText("Graph doesn't have circuits.");
}

void SortareTopologicaV2::on_setOriented_clicked()
{
	m_graph.setOriented();
}

void SortareTopologicaV2::on_sortedButton_clicked()
{
	if (m_graph.getCircuitStatus())
	{
		ui.sortedLabel->setText("Graph has circuits. Can't topologic sort.");
	}
	else
	{
		std::vector<Node*> result = m_graph.topologicalSort();

		sortFile.open("topologicSort.txt");
		for (uint32_t index = 0; index < result.size(); index++)
		{
			sortFile << result[index]->getValue() << " ";
		}
		sortFile.close();
		ui.sortedLabel->setText("Topologic sort has been saved.");
	}
}

void SortareTopologicaV2::on_sortedGraphButton_clicked()								//Doesn't work
{	
	graphWindow.setMatrix(m_graph.getMatrix());
	graphWindow.setNodes(m_graph.getNodes());
	graphWindow.update();
	//graphWindow.update();
	this->hide();
	graphWindow.show();
}

void SortareTopologicaV2::on_treeCheckButton_clicked()
{
	bool state = m_graph.isTree();
	if (state)
	{
		ui.isTreeLabel->setText("Graph is a Tree.");
	}
	else ui.isTreeLabel->setText("Graph isn't a Tree.");
}

void SortareTopologicaV2::on_rootButton_clicked()
{
	Node* root = m_graph.getRoot();
	if (root != nullptr)
		ui.rootLabel->setText(QString::number(root->getValue()));
	else ui.rootLabel->setText("No root.");
}
