#include "Graph.h"
#include "qline.h"
#include <queue>
#include <numeric>

Graph::Graph() = default;

Graph::~Graph()
{
    for (auto& entry : m_adjacencyList)
    {
        delete entry.first;
    }
}

void Graph::addNode(Node* node)
{
    if (m_adjacencyList.find(node) == m_adjacencyList.end())
    {
        m_adjacencyList[node] = std::vector<std::pair<Node*, double>>();
        nodeMapById[node->getID()] = node;
    }
}

void Graph::addEdge(Node* from, Node* to, double weight)
{
    addNode(from);
    addNode(to);

    m_adjacencyList[from].emplace_back(to, weight);
    m_adjacencyList[to].emplace_back(from, weight);
}

std::vector<std::pair<Node*, double>> Graph::getNeighbors(Node* node) const
{
    if (m_adjacencyList.find(node) != m_adjacencyList.end())
    {
        return m_adjacencyList.at(node);
    }
    else
    {
        return {};
    }
}

Node* Graph::getNodeById(uint32_t id) const
{
    auto it = nodeMapById.find(id);
    return (it != nodeMapById.end()) ? it->second : nullptr;
}

std::unordered_map<Node*, std::vector<std::pair<Node*, double>>> Graph::getAdjacencyList()
{
    return m_adjacencyList;
}

Node* Graph::getNodeAtPosition(const QPoint& position) const
{
    Node* closestNode = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (const auto& entry : m_adjacencyList)
    {
        Node* currentNode = entry.first;
        QPoint nodePosition = currentNode->getPos();

        double distance = QLineF(position, nodePosition).length();

        if (distance < minDistance)
        {
            minDistance = distance;
            closestNode = currentNode;
        }
    }

    return closestNode;
}

std::pair<std::vector<Node*>,double> Graph::dijkstra(Node* start, Node* end)
{
    //Priority Queue:lista de weights si nodul destinatie (Minheap--greater)
    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<>> pq;
    //Unordered Map: lista de key:nod destinatie si value:weight ul coresp
    std::unordered_map<Node*, double> distance;
    //Unordered Map: lista de key:nod si value:predecesorul lui
    std::unordered_map<Node*, Node*> previous;

    //INITIALIZARI:
    //Se initializeaza distantele cu invinit, predecesorii cu nullptr
    for (auto& entry : m_adjacencyList)
    {
        Node* current = entry.first;
        distance[current] = std::numeric_limits<double>::infinity();
        previous[current] = nullptr;
    }

    //Distanta de la start la start e setata la 0
    distance[start] = 0;
    pq.push({ 0, start });

    //Cat timp nu am ajuns la nodul destinatie (end)
    while (!pq.empty())
    {
        //Se extrage drumul de cost minim din pq
        auto [dist, current] = pq.top();
        pq.pop();

        //Daca s-a ajuns la final oprim while-ul
        if (current == end)
            break;

        //Iteram prin nodurile adiacente nodului corespunzator top pq
        for (const auto& neighbor : m_adjacencyList[current])
        {
            //Calculam distanta
            Node* nextNode = neighbor.first;
            double weight = neighbor.second;
            double newDist = distance[current] + weight;

            //Daca distanta calculata catre nodul adiacent curent (nextNode) este mai mica decat distanta inregistrata
            //anterior, actualizam distanta si informatiile despre predecesor
            //adaugam in pq informatiile
            if (newDist < distance[nextNode])
            {
                distance[nextNode] = newDist;
                previous[nextNode] = current;
                pq.push({ newDist, nextNode });
            }
        }
    }

    //pt calculat cost total (cost of transpor label)

    std::vector<Node*> path;
    Node* current = end;
    while (current != nullptr)
    {
        path.push_back(current);
        current = previous[current];
    }

    std::reverse(path.begin(), path.end());

    double totalCost = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        Node* current = path[i];
        Node* next = path[i + 1];

        auto it = std::find_if(
            m_adjacencyList[current].begin(),
            m_adjacencyList[current].end(),
            [next](const auto& edge) { return edge.first == next; }
        );

        if (it != m_adjacencyList[current].end())
        {
            totalCost += it->second;
        }
    }

    return std::make_pair(path, totalCost);
}

double Graph::getTotalCost(const std::vector<std::pair<Node*, double>>& edges)
{
    return std::accumulate(
        edges.begin(),
        edges.end(),
        0.0,
        [](double sum, const std::pair<Node*, double>& edge) {
            return sum + edge.second;
        }
    );
}

