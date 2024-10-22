#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

struct Node
{
    int vertex;
    double cost;
    double heuristic;
    Node *parent;

    Node(int v, double c, double h, Node *p = nullptr) : vertex(v), cost(c), heuristic(h), parent(p) {}

    double totalCost() const
    {
        return cost + heuristic;
    }

    bool operator>(const Node &other) const
    {
        return totalCost() > other.totalCost();
    }
};

double heuristic(int current, const vector<double> &heuristics)
{
    return heuristics[current];
}

vector<int> reconstructPath(Node *node)
{
    vector<int> path;
    while (node)
    {
        path.push_back(node->vertex);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> aStar(const vector<vector<pair<int, int>>> &adjList, int start, int goal, const vector<double> &heuristics)
{
    priority_queue<Node, vector<Node>, greater<>> openSet;
    unordered_map<int, double> gScore;
    unordered_map<int, Node *> allNodes;

    for (int i = 0; i < adjList.size(); ++i)
    {
        gScore[i] = numeric_limits<double>::infinity();
    }

    gScore[start] = 0;
    openSet.emplace(start, 0, heuristic(start, heuristics));
    allNodes[start] = new Node(start, 0, heuristic(start, heuristics));

    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();

        if (current.vertex == goal)
        {
            vector<int> path = reconstructPath(allNodes[goal]);

            for (auto &pair : allNodes)
            {
                delete pair.second;
            }
            return path;
        }

        for (const auto &neighbor : adjList[current.vertex])
        {
            int neighborVertex = neighbor.first;
            double edgeCost = neighbor.second;

            double tentative_gScore = gScore[current.vertex] + edgeCost;

            if (tentative_gScore < gScore[neighborVertex])
            {
                gScore[neighborVertex] = tentative_gScore;
                Node *neighborNode = new Node(neighborVertex, tentative_gScore, heuristic(neighborVertex, heuristics), new Node(current));

                openSet.push(*neighborNode);
                if (allNodes.find(neighborVertex) != allNodes.end())
                {
                    delete allNodes[neighborVertex];
                }
                allNodes[neighborVertex] = neighborNode;
            }
        }
    }

    for (auto &pair : allNodes)
    {
        delete pair.second;
    }

    return {};
}

int main()
{
    int numNodes;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    vector<vector<pair<int, int>>> adjList(numNodes);
    vector<double> heuristics(numNodes);

    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the edges (format: start_node end_node cost):" << endl;
    for (int i = 0; i < numEdges; ++i)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        adjList[u].emplace_back(v, cost);
        adjList[v].emplace_back(u, cost);
    }

    cout << "Enter the heuristic values for each node:" << endl;
    for (int i = 0; i < numNodes; ++i)
    {
        cout << "Heuristic value for node " << i << ": ";
        cin >> heuristics[i];
    }

    int start, goal;
    cout << "Enter the start node: ";
    cin >> start;
    cout << "Enter the goal node: ";
    cin >> goal;

    vector<int> path = aStar(adjList, start, goal, heuristics);

    if (!path.empty())
    {
        cout << "Path found: ";
        for (int vertex : path)
        {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found." << endl;
    }

    return 0;
}

/*
Enter the number of nodes: 5
Enter the number of edges: 6
Enter the edges (format: start_node end_node cost):
0 1 1
0 2 4
1 2 1
1 3 2
2 4 1
3 4 5
Enter the heuristic values for each node:
Heuristic value for node 0: 6
Heuristic value for node 1: 3
Heuristic value for node 2: 1
Heuristic value for node 3: 5
Heuristic value for node 4: 0
Enter the start node: 0
Enter the goal node: 4
*/