#include "graph.h"
#include <queue>

Graph::Graph()
{
	m_isOriented = false;
	m_hasCircuits = false;
	m_isTree = false;
	m_root = nullptr;
}

Graph::~Graph()
{
	for (Arch* arch : m_arches)
	{
		delete arch;
	}
	m_arches.clear();

	for (Node* node : m_nodes)
	{
		delete node;
	}
	m_nodes.clear();
}

void Graph::addNode(Node* node)
{
	m_nodes.emplace_back(node);

	for (uint32_t i = 0; i < m_nodes.size(); i++)
	{
		if (i == node->getValue() - 1)
		{
			std::vector<bool> line;
			for (uint32_t j = 0; j < node->getValue(); j++)
			{
				line.emplace_back(false);
			}
			m_adjacencyMatrix.emplace_back(line);
		}
		else
		{
			m_adjacencyMatrix[i].emplace_back(false);
		}
	}
}

void Graph::addArch(Arch* arch)
{
	m_arches.emplace_back(arch);
	arch->getFirstNode().addAdjacent(&arch->getSecondNode());

	m_adjacencyMatrix[arch->getFirstNode().getValue() - 1][arch->getSecondNode().getValue() - 1] = true;
	if (!m_isOriented)
	{
		m_adjacencyMatrix[arch->getSecondNode().getValue() - 1][arch->getFirstNode().getValue() - 1] = true;
		arch->getSecondNode().addAdjacent(&arch->getFirstNode());
	}
}

void Graph::deleteArch(Node* firstNode, Node* secondNode)
{
	for (auto it = m_arches.begin(); it != m_arches.end(); ++it) {
		Arch* currentArch = *it;
		if (currentArch->getFirstNode().getValue() == firstNode->getValue()
			&& currentArch->getSecondNode().getValue() == secondNode->getValue())
		{
			m_arches.erase(it);
			delete currentArch;
			break;
		}
	}
}

void Graph::setOriented()
{
	m_isOriented = true;
}

void Graph::setHasCircuits()
{
	m_hasCircuits = true;
}

void Graph::setNodes(std::vector<Node*> nodes)
{
	m_nodes = nodes;
}

void Graph::setArches(std::vector<Arch*> arches)
{
	m_arches = arches;
}

void Graph::setAdjacencyMatrix(std::vector<std::vector<bool>> matrix)
{
	m_adjacencyMatrix = matrix;
}

void Graph::modifyArch(uint32_t x, uint32_t y, bool state)
{
	m_adjacencyMatrix[x][y] = state;
	if (!m_isOriented)
		m_adjacencyMatrix[y][x] = state;
}

std::vector<Node*> Graph::getNodes()
{
	return m_nodes;
}

std::vector<Arch*> Graph::getArches()
{
	return m_arches;
}

std::vector<std::vector<bool>> Graph::getMatrix()
{
	return m_adjacencyMatrix;
}

bool Graph::getType()
{
	return m_isOriented;
}

bool Graph::getCircuitStatus()
{
	return m_hasCircuits;
}

Node* Graph::getNodeAtPosition(const QPoint& position) const
{
	for (Node* node : m_nodes)
	{
		if (node->getBoundingBox().contains(position))
		{
			return node;
		}
	}

	return nullptr;
}

Node* Graph::getNode(uint32_t index) const
{
	if (index >= 0 && index < m_nodes.size())
		return m_nodes[index];
}

void Graph::writeToFile(std::ofstream& file)
{
	for (uint32_t i = 0; i < m_nodes.size(); i++)
	{
		for (uint32_t j = 0; j < m_nodes.size(); j++)
		{
			file << m_adjacencyMatrix[i][j] << " ";
		}
		file << "\n";
	}
}

std::vector<Node*> Graph::depthFirstTraversal(Node* startNode)
{
	//INITIALIZARI
	std::vector<Node*> U = m_nodes;
	auto it = U.begin() + startNode->getValue() - 1;
	U.erase(it);
	std::stack<Node*> V;
	V.push(startNode);
	std::vector<Node*> W;
	std::vector<Node*> p;
	std::vector<uint32_t> t1;
	std::vector<uint32_t> t2;
	std::vector<uint32_t> vis;
	uint32_t t = 1;
	for (auto& node : m_nodes)
	{
		p.emplace_back(nullptr);
		t1.emplace_back(std::numeric_limits<int>::max());
		t2.emplace_back(std::numeric_limits<int>::max());
		vis.emplace_back(0);
	}
	t1[startNode->getValue() - 1] = 1;

	//ALGORITM
	while (!V.empty())
	{
		Node* x = V.top();
		vis[x->getValue() - 1] = 1;													//PT CIRCUITE
		std::vector<Node*> A = x->getAdjacent();

		auto it = U.begin();
		bool foundAdjacent = false;
		while (it != U.end())
		{
			Node* y = *it;
			if (m_adjacencyMatrix[x->getValue() - 1][y->getValue() - 1] == true)
			{
				V.push(y);
				p[y->getValue() - 1] = x;
				t1[y->getValue() - 1] = ++t;
				it = U.erase(it);
				foundAdjacent = true;
				break;
			}
			else
			{
				++it;
			}
		}
		if (!foundAdjacent)
		{
			if (!V.empty())
				V.pop();
			W.emplace_back(x);
			t2[x->getValue() - 1] = ++t;
			vis[x->getValue() - 1] = 2;												//PT CIRCUITE
		}
		for (auto& y : A)															//PT CIRCUITE
		{
			if (std::find(U.begin(), U.end(), y) == U.end())
				if (vis[y->getValue() - 1] == 1)
				{
					m_hasCircuits = true;
				}
		}
	}
	//std::reverse(W.begin(), W.end()); -> pt afisarea ca in exemplul la lab 
	return W;
}

void Graph::depthFirstTraversalUtil(Node* startNode, std::vector<Node*>& parent)
{
	//INITIALIZARI
	std::vector<Node*> U = m_nodes;
	auto it = U.begin() + startNode->getValue() - 1;
	U.erase(it);
	std::stack<Node*> V;
	V.push(startNode);
	std::vector<Node*> W;
	std::vector<Node*> p;
	std::vector<uint32_t> t1;
	std::vector<uint32_t> t2;
	std::vector<uint32_t> vis;
	uint32_t t = 1;
	for (auto& node : m_nodes)
	{
		t1.emplace_back(std::numeric_limits<int>::max());
		t2.emplace_back(std::numeric_limits<int>::max());
		vis.emplace_back(0);
	}
	t1[startNode->getValue() - 1] = 1;

	//ALGORITM
	while (!V.empty())
	{
		Node* x = V.top();
		vis[x->getValue() - 1] = 1;													//PT CIRCUITE
		std::vector<Node*> A = x->getAdjacent();

		auto it = U.begin();
		bool foundAdjacent = false;
		while (it != U.end())
		{
			Node* y = *it;
			if (m_adjacencyMatrix[x->getValue() - 1][y->getValue() - 1] == true)
			{
				V.push(y);
				p[y->getValue() - 1] = x;
				t1[y->getValue() - 1] = ++t;
				it = U.erase(it);
				foundAdjacent = true;
				break;
			}
			else
			{
				++it;
			}
		}
		if (!foundAdjacent)
		{
			if (!V.empty())
				V.pop();
			W.emplace_back(x);
			t2[x->getValue() - 1] = ++t;
			vis[x->getValue() - 1] = 2;												//PT CIRCUITE
		}
		for (auto& y : A)															//PT CIRCUITE
		{
			if (std::find(U.begin(), U.end(), y) == U.end())
				if (vis[y->getValue() - 1] == 1)
				{
					m_hasCircuits = true;
				}
		}
	}
	parent = p;
}

std::vector<Node*> Graph::topologicalSort()
{
	if (m_hasCircuits)
		exit(1);
	//INITIALIZARI
	Node* startNode = m_nodes[0];
	std::vector<Node*> U = m_nodes;
	auto it = U.begin() + startNode->getValue() - 1;
	U.erase(it);
	std::stack<Node*> V;
	V.push(startNode);
	std::vector<std::pair<uint32_t, Node*>> W;										//PT SORT TOP
	std::vector<Node*> p;
	std::vector<uint32_t> t1;
	std::vector<uint32_t> t2;
	uint32_t t = 1;
	for (auto& node : m_nodes)
	{
		p.emplace_back(nullptr);
		t1.emplace_back(std::numeric_limits<int>::max());
		t2.emplace_back(std::numeric_limits<int>::max());
	}
	t1[startNode->getValue() - 1] = 1;

	//ALGORITM
	while (W.size() != m_nodes.size())												//PT PARCURGERE TOTALA
	{
		while (!V.empty())
		{
			Node* x = V.top();
			std::vector<Node*> A = x->getAdjacent();

			auto it = U.begin();
			bool foundAdjacent = false;
			while (it != U.end())
			{
				Node* y = *it;
				if (m_adjacencyMatrix[x->getValue() - 1][y->getValue() - 1] == true)
				{
					V.push(y);
					p[y->getValue() - 1] = x;
					t1[y->getValue() - 1] = ++t;
					it = U.erase(it);
					foundAdjacent = true;
					break;
				}
				else
				{
					++it;
				}
			}
			if (!foundAdjacent)
			{
				if (!V.empty())
					V.pop();
				t2[x->getValue() - 1] = ++t;
				W.emplace_back(std::make_pair(t, x));
			}
		}
		if (!U.empty())																	//PT PARCURGERE TOTALA
		{
			Node* nextNode = U[0];
			U.erase(std::remove(U.begin(), U.end(), nextNode), U.end());
			V.push(nextNode);
		}
	}

	//Ordonarea lui W dupa timpii t2
	std::sort(W.begin(), W.end(), std::greater<>());
	std::vector<Node*> result;
	for (auto& node : W)
	{
		result.emplace_back(node.second);
	}
	return result;
}

Graph Graph::sortGraph()						//Doesn't work
{
	Graph modifiedGraph = *this;

	//...

	return modifiedGraph;
}

bool Graph::hasCycle()
{
	std::vector<uint32_t> vis(m_nodes.size(), 0);
	std::queue<std::pair<Node*, Node*>> queue;

	for (Node* startNode : m_nodes) {
		if (vis[startNode->getValue() - 1] == 0) {
			queue.push({ startNode, nullptr });

			while (!queue.empty()) {
				auto currentPair = queue.front();
				Node* current = currentPair.first;
				Node* parent = currentPair.second;
				queue.pop();

				if (vis[current->getValue() - 1] == 1) {
					return true;
				}

				vis[current->getValue() - 1] = 1;

				for (auto& neighbor : current->getAdjacent()) {
					if (neighbor != parent) {
						queue.push({ neighbor, current });
					}
				}
			}
		}
	}
}

bool Graph::isTree() 
{
	if (m_isOriented) {
		qDebug() << "Graful orientat nu poate fi un arbore.";
		return false;
	}

	if (m_hasCircuits) {
		qDebug() << "Graful cu circuite nu poate fi un arbore.";
		return false;
	}

	for (Node* node : m_nodes) 
	{
		uint32_t index = node->getValue();
		bool found = false;
		for (Arch* arch : m_arches) {
			if (arch->getFirstNode().getValue() == index || arch->getSecondNode().getValue() == index) {
				found = true;
				break;
			}
		}
		if (!found) {
			qDebug() << "Graful contine noduri izolate. Nu este un arbore.";
			return false;
		}
	}

	if (m_arches.size() != m_nodes.size() - 1)
		return false;

	if (hasCycle())
		return false;

	m_isTree = true;
	return true;
}

Node* Graph::getRoot() {
	std::unordered_set<int> visited;

	for (int i = 0; i < m_nodes.size(); i++) {
		int nodeCount = nodeVarchPDF1(m_nodes[i], visited);

		if (nodeCount == m_nodes.size()) {
			bool hasIncomingEdges = false;

			for (auto& arc : m_arches) {
				if (arc->getSecondNode().getValue() == i + 1) {
					hasIncomingEdges = true;
					break;
				}
			}

			if (!hasIncomingEdges) {
				return m_nodes[i];
			}
		}

		visited.clear();
	}

	return nullptr;
}

int Graph::nodeVarchPDF1(Node* startNode, std::unordered_set<int>& visited) {
	std::vector<int> U(m_nodes.size(), 0);
	std::stack<int> V;

	V.push(startNode->getValue());

	while (!V.empty()) {
		int head = V.top();
		V.pop();

		U[head - 1] = 1;

		if (visited.find(head) == visited.end()) {
			visited.insert(head);

			for (auto& arc : m_arches) {
				int neighbor = -1;

				if (arc->getFirstNode().getValue() == head) {
					neighbor = arc->getSecondNode().getValue();
				}
				else if (arc->getSecondNode().getValue() == head) {
					neighbor = arc->getFirstNode().getValue();
				}

				if (neighbor != -1 && !U[neighbor - 1]) {
					V.push(neighbor);
				}
			}
		}
	}

	return visited.size();
}
