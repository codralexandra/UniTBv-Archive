#pragma once
#include <iostream>
#include <QPoint.h>
class Node
{
public:
	Node() { m_id = -1; }
	~Node(){}

	void setId(const uint32_t& id);
	void setPos(const uint32_t& x, const uint32_t& y);
	void setMapPos(const QPoint& pos);

	uint32_t getID();
	QPoint getPos();
	QPoint getMapPos();

private:
	uint32_t m_id;
	QPoint m_pos;
	QPoint m_mapPos;
};

