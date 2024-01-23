#include "Node.h"
#include <qDebug>

Node::Node()
{
	m_value = 0;
	isEnd = false;
	visited = false;
	predecessor = nullptr;
	isGoodRoad = false;
	m_x = -1;
	m_y = -1;
}

Node::~Node()
{
	delete predecessor;
}

void Node::setValue(int value)
{
	m_value = value;
}

void Node::setEnd(bool state)
{
	isEnd = state;
}

void Node::setVisited()
{
	qDebug() << "Setting visited for Node " << m_value << " to true.";
	visited = true;
}

void Node::setPredecessor(Node* node)
{
	if (node == nullptr)
		predecessor = nullptr;
	else predecessor = node;
}

void Node::setIsGoodRoad(bool state)
{
	isGoodRoad = state; //exception thrown access violation writing location
}

void Node::setX(int x)
{
	m_x = x;
}

void Node::setY(int y)
{
	m_y = y;
}


int Node::getValue()
{
	return m_value;
}

bool Node::getIsEnd()
{
	return isEnd;
}

bool Node::getVisited()
{
	return visited;
}

Node* Node::getPredecessor()
{
	return predecessor;
}

bool Node::getIsGoodRoad()
{
	return isGoodRoad;
}

int Node::getX()
{
	return m_x;
}

int Node::getY()
{
	return m_y;
}
