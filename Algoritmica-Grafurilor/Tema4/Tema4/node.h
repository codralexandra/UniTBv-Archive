#pragma once
#include <cstdint>
#include <vector>
#include "qpoint.h"
#include "qrect.h"

class Node
{
public:
	Node();
	~Node();

	void setValue(const uint32_t& value);
	void setPosition(const QPoint& position);
	void setVisited();
	void setOverlap(bool state);
	
	uint32_t getValue() const;
	std::vector<Node*> getAdjacent();
	QPoint getPosition();
	bool getVisitedStatus();
	bool getOverlapState();

	void addAdjacent(Node* node);

	QRect getBoundingBox();

	bool isOverlapping(Node& node);

	bool operator<(const Node& other) const {
		return getValue() < other.getValue();
	}

	bool operator()(const Node* first, const Node* second) const {
		return *first < *second;
	}

	bool operator==(const Node* second) const {
		return m_value == second->getValue();
	}

	bool operator!=(Node second) const {
		return m_value != second.getValue();
	}

private:
	uint32_t m_value;
	std::vector<Node*> m_adjacent;
	QPoint m_position;
	bool m_isVisited;
	bool m_isOverlapping;
};

