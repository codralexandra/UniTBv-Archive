#include "graph.h"
Graph::Graph()
{
    isOriented=false;
    numNodes=0;
}
vector<Node> Graph::getNodes(){
    return nodes;
}
vector<Arch> Graph::getArches(){
    return arches;
}

bool Graph::getIsOriented(){
    return isOriented;
}

void Graph::addNode(QPoint p){
    Node n;
    n.setCoord(p);
    n.setValue(nodes.size()+1);
    nodes.push_back(n);
    updateMatrix();
    saveMatrixToFile();
}
void Graph::addNode(Node n){
    nodes.push_back(n);
    updateMatrix();
    saveMatrixToFile();
}
void Graph::addArch(Arch a){
    arches.push_back(a);
    updateMatrix();
    saveMatrixToFile();
}
void Graph::addArch(Node n1, Node n2){
    arches.push_back(Arch(n1,n2));
    updateMatrix();
    saveMatrixToFile();
}
void Graph::setIsOriented(bool value){
    isOriented=value;
}
void Graph::setMatriceAdiacenta(vector<vector<int>> matrice){
    matrAdiacenta = matrice;
}
bool Graph::arcExists(const Node& n1, const Node& n2, bool checkDirection) {
    //checkDirection = true -> acelasi sens, false -> sens opus
    vector<Arch> arches = getArches();
    for (Arch& a : arches) {
        if (checkDirection) {
            if (a.getFirstNode() == n1 && a.getSecondNode() == n2) {
                return true;
            }
        } else {
            if ((a.getFirstNode() == n2 && a.getSecondNode() == n1)) {
                return true;
            }
        }
    }
    return false;
}
int Graph::getNodeIndex(const Node& node)
{
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i] == node)
        {
            return i;
        }
    }
    return -1;
}
void Graph::updateMatrix(){
    numNodes = nodes.size();
    matrAdiacenta = std::vector<std::vector<int>>(numNodes, std::vector<int>(numNodes, 0));
    for (Arch& arch : arches)
    {
        int node1Index = getNodeIndex(arch.getFirstNode());
        int node2Index = getNodeIndex(arch.getSecondNode());
        matrAdiacenta[node1Index][node2Index] = 1;
        if (!isOriented)
        {
            matrAdiacenta[node2Index][node1Index] = 1;
        }
    }
}
void Graph::saveMatrixToFile(){
    std::ofstream outputFile("C:/Users/ELITEBOOK/Documents/Facultate/AG/Graph-WorkingVersion/matrice_adiacenta.txt");
    if (outputFile.is_open())
    {
        for (const auto& row : matrAdiacenta)
        {
            for (int val : row)
            {
                outputFile << val << ' ';
            }
            outputFile << '\n';
        }
        outputFile.close();
    }
    else cout<<"Fisierul nu a putut fi deschis.";
}
