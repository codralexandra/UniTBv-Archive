#pragma once
#include "arch.h"
#include "UnionFind.h"
#include <vector>
#include <fstream>
#include <stack>
#include <qdebug.h>
#include <limits>
#include <algorithm>
#include <unordered_set>

class Graph
{
public:
	Graph();
	~Graph();

	void addNode(Node* node);
	void addArch(Arch* arch);

	void setNodes(std::vector<Node*> nodes);
	void setArches(std::vector<Arch*> arches);
	void setAdjacencyMatrix(std::vector<std::vector<bool>> matrix);

	std::vector<Node*> getNodes();
	std::vector<Arch*> getArches();
	std::vector<Arch> getMinArches();
	std::vector<std::vector<bool>> getMatrix();
	Node* getNodeAtPosition(const QPoint& position) const;
	Node* getNode(uint32_t index) const;
	Arch getArch(const Node& firstNode, const Node& secondNode);

	//----------------Tema 4 Algoritmi:

	void primAlgorithm();
	void kruskalAlgorithm();

private:
	std::vector<Node*> m_nodes;
	std::vector<Arch*> m_arches;
	std::vector<Arch> m_minCostArches;
	std::vector <std::vector<bool>> m_adjacencyMatrix;
	bool m_isOriented;
};

