#pragma once
#include "node.h"

class Arch
{
public:
	Arch(Node* firstNode, Node* secondNode);
	~Arch();

	void setFirstNode(Node& node);
	void setSecondNode(Node& node);

	Node& getFirstNode();
	Node& getSecondNode();

private:
	Node* m_firstNode;
	Node* m_secondNode;
};

