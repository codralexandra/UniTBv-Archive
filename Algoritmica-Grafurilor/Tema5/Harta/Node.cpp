#include "Node.h"

void Node::setId(const uint32_t& id)
{
	m_id = id;
}

void Node::setPos(const uint32_t& x, const uint32_t& y)
{
	m_pos.setX(x);
	m_pos.setY(y);
}

void Node::setMapPos(const QPoint& pos)
{
	m_mapPos = pos;
}

uint32_t Node::getID()
{
	return m_id;
}

QPoint Node::getPos()
{
	return m_pos;
}

QPoint Node::getMapPos()
{
	return m_mapPos;
}
