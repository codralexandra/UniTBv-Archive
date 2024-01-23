#include "arch.h"

Arch::Arch(Node* firstNode, Node* secondNode)
{
	m_firstNode = firstNode;
	m_secondNode = secondNode;
}

Arch::~Arch()
{
	/* EMPTY */
	//check if need to set to nullptr
}

void Arch::setFirstNode(Node& node)
{
	m_firstNode = &node;
}

void Arch::setSecondNode(Node& node)
{
	m_secondNode = &node;
}

Node& Arch::getFirstNode()
{
	return *m_firstNode;
}

Node& Arch::getSecondNode()
{
	return *m_secondNode;
}
