#include "graph.h"
#include <set>
#include <queue>
#include <algorithm>
#include <set>

struct NodePtrComparator {
	bool operator()(const Node* lhs, const Node* rhs) const {
		return *lhs < *rhs;
	}
};

Graph::Graph()
{
	m_isOriented = false;
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

std::vector<Node*> Graph::getNodes()
{
	return m_nodes;
}

std::vector<Arch*> Graph::getArches()
{
	return m_arches;
}

std::vector<Arch> Graph::getMinArches()
{
	return m_minCostArches;
}

std::vector<std::vector<bool>> Graph::getMatrix()
{
	return m_adjacencyMatrix;
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

Arch Graph::getArch(const Node& firstNode, const Node& secondNode)
{
	Arch null_arch;
	for (auto& arch : m_arches)
	{
		if ((arch->getFirstNode().getValue() == firstNode.getValue() &&
			arch->getSecondNode().getValue() == secondNode.getValue()) ||
			(arch->getFirstNode().getValue() == secondNode.getValue() &&
				arch->getSecondNode().getValue() == firstNode.getValue()))
			return *arch;
	}
	return null_arch;
}

void Graph::primAlgorithm()
{
	m_minCostArches.clear();
	
	//priority_queue (find complexiti e log) -> (cost, *nod), nodul conectat prin arch-u cu costul respectiv, greater pt sortare crescatoare dupa cost
	std::priority_queue<std::pair<uint32_t, Node*>,
		std::vector<std::pair<uint32_t, Node*>>,
		std::greater<std::pair<uint32_t, Node*>>> possibleArches;

	std::unordered_set<Node*> visitedNodes;

	//nodul din care pornim algoritmul 
	Node* startNode = m_nodes[0];
	visitedNodes.insert(startNode);
	startNode->setVisited();

	//initializam possibleArches cu toatea arcele care incep din nodul de start
	for (Node* adjacent : startNode->getAdjacent())
	{
		Arch arch = getArch(*startNode, *adjacent);
		possibleArches.push({ arch.getCost(), adjacent });
	}
	std::unordered_map<Node*, Arch> minCostArcs;
	for (Node* adjacent : startNode->getAdjacent())
	{
		Arch arch = getArch(*startNode, *adjacent);

		//update minCostArcs for the adjacent node
		if (minCostArcs.find(adjacent) == minCostArcs.end() || arch.getCost() < minCostArcs[adjacent].getCost())
		{
			minCostArcs[adjacent] = arch;
		}

		possibleArches.push({ arch.getCost(), adjacent });
	}

	while (!possibleArches.empty() && visitedNodes.size() < m_nodes.size())
	{
		//extract the arc with the minimum cost
		uint32_t cost = possibleArches.top().first;
		Node* currentNode = possibleArches.top().second;
		possibleArches.pop();

		//if the node is already visited, skip it
		if (visitedNodes.count(currentNode) > 0)
			continue;

		//mark the current node as visited
		currentNode->setVisited();
		visitedNodes.insert(currentNode);

		//process the arc and add it to the result
		if (minCostArcs.find(currentNode) != minCostArcs.end())
		{
			m_minCostArches.emplace_back(minCostArcs[currentNode]);
		}

		//process adjacent nodes
		for (Node* adjacent : currentNode->getAdjacent())
		{
			if (!adjacent->getVisitedStatus())
			{
				Arch arch = getArch(*currentNode, *adjacent);

				// Update minCostArcs for the adjacent node
				if (minCostArcs.find(adjacent) == minCostArcs.end() || arch.getCost() < minCostArcs[adjacent].getCost())
				{
					minCostArcs[adjacent] = arch;
					qDebug() << "Updated minCostArcs for node " << adjacent->getValue() << " with cost " << arch.getCost();
				}

				possibleArches.push({ arch.getCost(), adjacent });
			}
		}
		
	}
}

void Graph::kruskalAlgorithm()
{
	std::vector<Arch*> sortedArches = m_arches;
	//Sortarea arcelor dupa cost
	std::sort(sortedArches.begin(), sortedArches.end(), [](const Arch* a, const Arch* b) {
		return a->getCost() < b->getCost();
		});

	m_minCostArches.clear(); //A'

	UnionFind uf(m_arches.size());

	for (uint32_t i = 0; i < m_arches.size(); i++)
	{
		Arch* currentArch = sortedArches[i];
		uint32_t u = currentArch->getFirstNode().getValue();
		uint32_t v = currentArch->getSecondNode().getValue();

		//Verifica daca currentArch formeaza un ciclu in A'
		if (uf.Find(u) != uf.Find(v))
		{
			m_minCostArches.push_back(*currentArch);
			uf.Union(u, v);
		}
	}
}
