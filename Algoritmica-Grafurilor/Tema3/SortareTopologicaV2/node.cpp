#include "node.h"

Node::Node()
{
	m_value = -1;
	m_position.setX(0);
	m_position.setY(0);
	m_isVisited = false;
}

Node::~Node()
{
	/* EMPTY */
}

void Node::setValue(const uint32_t& value)
{
	m_value = value;
}

void Node::setPosition(const QPoint& position)
{
	m_position = position;
}

void Node::setVisited()
{
	m_isVisited = true;
}

void Node::setOverlap(bool state)
{
	m_isOverlapping = state;
}

uint32_t Node::getValue() const
{
	return m_value;
}

std::vector<Node*> Node::getAdjacent() const
{
	return m_adjacent;
}

QPoint Node::getPosition() const
{
	return m_position;
}

bool Node::getVisitedStatus() const
{
	return m_isVisited;
}

bool Node::getOverlapState() const
{
	return m_isOverlapping;
}

void Node::addAdjacent(Node* node)
{
	m_adjacent.emplace_back(node);
}

QRect Node::getBoundingBox() const
{
	int nodeRadius = 40;
	return QRect(m_position.x() - nodeRadius, m_position.y() - nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
}

bool Node::isOverlapping(const Node& node) const
{
	int dx = m_position.x() - node.getPosition().x();
	int dy = m_position.y() - node.getPosition().y();
	int distance = std::sqrt(dx * dx + dy * dy);

	int radiusSum = 20;

	return distance <= radiusSum;
}
