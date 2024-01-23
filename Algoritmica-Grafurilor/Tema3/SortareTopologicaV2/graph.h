#pragma once
#include "arch.h"
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
	void deleteArch(Node* firstNode, Node* secondNode);

	void setOriented();
	void setHasCircuits();
	void setNodes(std::vector<Node*> nodes);
	void setArches(std::vector<Arch*> arches);
	void setAdjacencyMatrix(std::vector<std::vector<bool>> matrix);

	void modifyArch(uint32_t x, uint32_t y, bool state);

	std::vector<Node*> getNodes();
	std::vector<Arch*> getArches();
	std::vector<std::vector<bool>> getMatrix();
	bool getType();
	bool getCircuitStatus();
	Node* getNodeAtPosition(const QPoint& position) const;
	Node* getNode(uint32_t index) const;

	void writeToFile(std::ofstream& file);

	std::vector<Node*> depthFirstTraversal(Node* startNode);

	void depthFirstTraversalUtil(Node* startNode, std::vector<Node*>& parent);

	std::vector<Node*> topologicalSort();

	Graph sortGraph(); //Doesn't work

	bool hasCycle();

	bool isTree();

	Node* getRoot();

	int nodeVarchPDF1(Node* startNode, std::unordered_set<int>& visited);

private:
	std::vector<Node*> m_nodes;
	std::vector<Arch*> m_arches;
	std::vector <std::vector<bool>> m_adjacencyMatrix;
	bool m_isOriented;
	bool m_hasCircuits;
	bool m_isTree;
	Node* m_root;
};

