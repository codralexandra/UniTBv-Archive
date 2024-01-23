#include "Graph.h"
#include <qDebug>

Graph::Graph() 
{
	startNode = nullptr;
}
Graph::~Graph() 
{ 
}

std::vector<Node>& Graph::getNodes()
{
	return m_nodes;
}

std::vector<std::vector<int>> Graph::getMatrix()
{
	return m_matriceAdiacenta;
}

std::vector<std::vector<int>> Graph::getSolutionMatrix()
{
    return solutionMatrix;
}

std::vector<std::vector<int>> Graph::getLabyrinthMatrix()
{
    return labyrinthMatrix;
}

Node Graph::getStartNode()
{
    return *startNode;
}

void Graph::setMatrix(std::vector<std::vector<int>> matrix)
{
	m_matriceAdiacenta = matrix;
}

void Graph::setStart(Node* node)
{
	startNode = node;
}

void Graph::setSolutionMatrix(std::vector<std::vector<int>> matrix)
{
    solutionMatrix = matrix;
}

void Graph::setLabyrinthMatrix(std::vector<std::vector<int>> matrix)
{
    labyrinthMatrix = matrix;
}

void Graph::addNode(const Node& node)
{
	m_nodes.push_back(node);
}

void Graph::breadthFirst()
{
    std::queue<Node*> visitedNotAnalized;
    visitedNotAnalized.push(startNode);
    startNode->setVisited();
    std::vector<int> predecessors(getNodes().size(), 0);
    std::vector<Node*> adjacentNodes;

    while (!visitedNotAnalized.empty())
    {
        Node* toAnalize = visitedNotAnalized.front();
        for (int i = 0; i < m_matriceAdiacenta[0].size(); i++)
        {
            if (m_matriceAdiacenta[toAnalize->getValue()-1][i] == 1)
            {
                Node* adjacentNode = getNode(i + 1);
                if (!adjacentNode->getVisited())
                {
                    adjacentNodes.push_back(adjacentNode);
                    adjacentNode->setVisited();
                }
            }
        }

        for (int i = 0; i < adjacentNodes.size(); i++)
        {
            Node* adjacentNode = adjacentNodes[i];

            qDebug() << "Processing Node" << adjacentNode->getValue() << "with visited state:" << adjacentNode->getVisited();

            if (adjacentNode->getValue() != startNode->getValue())
            {
                adjacentNode->setPredecessor(toAnalize);
                predecessors[adjacentNode->getValue() - 1] = toAnalize->getValue();
                visitedNotAnalized.push(adjacentNode);

                qDebug() << "Node" << adjacentNode->getValue() << "added to the queue.";
            }
        }
        visitedNotAnalized.pop();
        adjacentNodes.clear();
    }
    m_predecessors = predecessors;
}

Node* Graph::getNode(int value)
{
	for (Node& node : getNodes())
	{
		if (node.getValue() == value)
			return &node;
	}
}

void Graph::exitRoad(Node& exitNode) //fix
{
    int x = exitNode.getValue() - 1; //in x punem indexul coresp nodului de iesire
    std::vector<int> pathNodes;
    while (m_predecessors[x] != 0)
    {
        pathNodes.emplace_back(m_predecessors[x]);
        x = m_predecessors[x] - 1;
    }
    for (int nodeIndex : pathNodes)
    {
        getNode(nodeIndex)->setIsGoodRoad(true);
    }
}
