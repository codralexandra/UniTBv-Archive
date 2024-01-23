#pragma once
#include "node.h"

class Arch
{
public:
	Arch() {
		m_firstNode = nullptr;
		m_secondNode = nullptr;
		m_cost = -1;
		m_isVisited = false;
	}
	Arch(Node* firstNode, Node* secondNode, uint32_t cost);
	~Arch();

	void setFirstNode(Node& node);
	void setSecondNode(Node& node);
	void setCost(uint32_t value);
	void setVisited(bool state);

	Node& getFirstNode() const;
	Node& getSecondNode() const;
	uint32_t getCost() const;
	bool getVisited();

	/*bool operator==(const Arch& other) const {
		return (this->getFirstNode() == &other.getFirstNode()) &&
			(this->getSecondNode() == &other.getSecondNode()) &&
			(this->getCost() == other.getCost());
	}*/

private:
	Node* m_firstNode;
	Node* m_secondNode;
	uint32_t m_cost;
	bool m_isVisited;
};

