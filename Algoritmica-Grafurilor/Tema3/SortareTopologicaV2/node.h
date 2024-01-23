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
	std::vector<Node*> getAdjacent() const;
	QPoint getPosition() const;
	bool getVisitedStatus() const;
	bool getOverlapState() const;

	void addAdjacent(Node* node);

	QRect getBoundingBox() const;

	bool isOverlapping(const Node& node) const;

private:
	uint32_t m_value;
	std::vector<Node*> m_adjacent;
	QPoint m_position;
	bool m_isVisited;
	bool m_isOverlapping;
};

