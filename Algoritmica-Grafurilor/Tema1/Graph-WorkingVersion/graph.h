#ifndef GRAPH_H
#define GRAPH_H
#include "arch.h"
#include <fstream>
#include <iostream>
using namespace std;
class Graph
{
    vector<Node> nodes;
    vector<Arch> arches;
    bool isOriented;
    vector<vector<int>> matrAdiacenta;
    int numNodes;
public:
    Graph();

    vector<Node> getNodes();
    vector<Arch> getArches();
    bool getIsOriented();

    void addNode(QPoint p);
    void addNode(Node n);
    void addArch(Arch a);
    void addArch(Node n1, Node n2);
    void setIsOriented(bool value);
    void setMatriceAdiacenta(vector<vector<int>> matrice);
    bool arcExists(const Node& n1, const Node& n2, bool checkDirection);
    int getNodeIndex(const Node& node);
    void updateMatrix();
    void saveMatrixToFile();
};
#endif // GRAPH_H

