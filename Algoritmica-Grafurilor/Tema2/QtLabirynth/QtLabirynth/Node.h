#pragma once

class Node
{
public:
	Node();
	~Node();

	void setValue(int value);
	void setEnd(bool state);
	void setVisited();
	void setPredecessor(Node* node);
	void setIsGoodRoad(bool state);
	void setX(int x);
	void setY(int y);

	int getValue();
	bool getIsEnd();
	bool getVisited();
	Node* getPredecessor();
	bool getIsGoodRoad();
	int getX();
	int getY();

private:
	int m_value;
	bool isEnd;
	bool visited;
	Node* predecessor;
	bool isGoodRoad;
	int m_x;
	int m_y;
};

