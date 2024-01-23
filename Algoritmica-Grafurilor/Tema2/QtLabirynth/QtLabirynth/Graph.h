#pragma once
#include "Node.h"
#include <vector>
#include <queue>
class Graph
{
public:
	Graph();
	~Graph();

	std::vector<Node>& getNodes();
	std::vector<std::vector<int>> getMatrix();
	std::vector<std::vector<int>> getSolutionMatrix();
	std::vector<std::vector<int>> getLabyrinthMatrix();

	Node getStartNode();

	void setMatrix(std::vector<std::vector<int>> matrix);
	void setStart(Node* node);
	void setSolutionMatrix(std::vector<std::vector<int>> matrix);
	void setLabyrinthMatrix(std::vector<std::vector<int>> matrix);

	void addNode(const Node& node);

	void breadthFirst();

	Node* getNode(int value);
	void exitRoad(Node& exitNode);

private:
	std::vector<Node> m_nodes;
	std::vector<std::vector<int>> m_matriceAdiacenta;
	std::vector<int> m_predecessors;
	Node* startNode;
	std::vector<std::vector<int>> labyrinthMatrix;
	std::vector<std::vector<int>> solutionMatrix;
};

