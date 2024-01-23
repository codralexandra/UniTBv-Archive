#pragma once
#include "Node.h"
#include <unordered_map>
class Graph
{
public:
    Graph();
    ~Graph();

    void addNode(Node* node);
    void addEdge(Node* from, Node* to, double weight);
    std::vector<std::pair<Node*, double>> getNeighbors(Node* node) const;
    Node* getNodeById(uint32_t id) const;
    std::unordered_map<Node*, std::vector<std::pair<Node*, double>>> getAdjacencyList();
    Node* getNodeAtPosition(const QPoint& position) const;
    std::pair<std::vector<Node*>,double> dijkstra(Node* start, Node* end);
    double getTotalCost(const std::vector<std::pair<Node*, double>>& edges);

private:
    std::unordered_map<Node*, std::vector<std::pair<Node*, double>>> m_adjacencyList;
    std::unordered_map<uint32_t, Node*> nodeMapById; //pt find-uri dupa id
};

