#include "arch.h"

Arch::Arch(Node* firstNode, Node* secondNode, uint32_t cost)
{
	m_firstNode = firstNode;
	m_secondNode = secondNode;
	m_cost = cost;
}

Arch::~Arch()
{
	/* EMPTY */
}

void Arch::setFirstNode(Node& node)
{
	m_firstNode = &node;
}

void Arch::setSecondNode(Node& node)
{
	m_secondNode = &node;
}

void Arch::setCost(uint32_t value)
{
	m_cost = value;
}

void Arch::setVisited(bool state)
{
	m_isVisited = state;
}

Node& Arch::getFirstNode() const
{
	return *m_firstNode;
}

Node& Arch::getSecondNode() const
{
	return *m_secondNode;
}

uint32_t Arch::getCost() const
{
	return m_cost;
}

bool Arch::getVisited()
{
	return m_isVisited;
}
