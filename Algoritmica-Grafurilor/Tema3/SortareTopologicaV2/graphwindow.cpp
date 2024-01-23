#include "graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GraphWindow::~GraphWindow()
{}

void GraphWindow::setMatrix(const std::vector<std::vector<bool>>& matrix)
{
	m_adjacencyMatrix = matrix;
    update();
}

void GraphWindow::setNodes(const std::vector<Node*>& nodes)
{
    m_nodes = nodes;
}

void GraphWindow::paintEvent(QPaintEvent* event)                    //Check coordonate system
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    uint32_t nodeRadius = 40;
    uint32_t nodeBorderWidth = 3;
    uint32_t lineWidth = 3;

    // DRAW ARCHES
    
    for (int i = 0; i < m_nodes.size(); ++i)
    {
        for (int j = 0; j < m_nodes.size(); ++j)
        {
            if (m_adjacencyMatrix[i][j])
            {
                QPen pen(Qt::black);
                pen.setWidth(lineWidth);
                painter.setPen(pen);

                int circle1X = m_nodes[i]->getPosition().x();
                int circle1Y = m_nodes[i]->getPosition().y();
                int circle2X = m_nodes[j]->getPosition().x();
                int circle2Y = m_nodes[j]->getPosition().y();

                double angle = std::atan2(circle2Y - circle1Y, circle2X - circle1X);

                int lineStartX = circle1X + static_cast<int>(10 * std::cos(angle));
                int lineStartY = circle1Y + static_cast<int>(10 * std::sin(angle));

                int lineEndX = circle2X - static_cast<int>(10 * std::cos(angle));
                int lineEndY = circle2Y - static_cast<int>(10 * std::sin(angle));

                painter.drawLine(lineStartX, lineStartY, lineEndX, lineEndY);
            }
        }
    }

    // ARCHES WITH ARROWS
        for (int i = 0; i < m_nodes.size(); ++i)
        {
            for (int j = 0; j < m_nodes.size(); ++j)
            {
                if (m_adjacencyMatrix[i][j])
                {
                    QPointF firstPos = m_nodes[i]->getPosition();
                    QPointF secondPos = m_nodes[j]->getPosition();

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
        }

    // DRAW NODES
    for (Node* node : m_nodes)
    {
        // Adjust the coordinates to the local coordinate system of graphWindow
        QPointF nodePosition = mapFromGlobal(node->getPosition());

        QRect circle(nodePosition.x() - nodeRadius / 2, nodePosition.y() - nodeRadius / 2, nodeRadius, nodeRadius);
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
