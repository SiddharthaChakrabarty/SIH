#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <string>

using namespace std;

struct Node
{
    string name;
    int heuristic;
    vector<pair<vector<string>, int>> children; // Pair of {child nodes (for AND/OR), cost}
    bool solved = false;                        // To track if the node is already solved
};

// Function to print the optimal path
void printPath(const vector<string> &path)
{
    cout << "Optimal Path: ";
    for (const auto &node : path)
    {
        cout << node << " ";
    }
    cout << endl;
}

// Recursive AO* algorithm function
int aostar(unordered_map<string, Node> &graph, const string &nodeName, vector<string> &path)
{
    Node &node = graph[nodeName];
    if (node.solved)
    {
        return node.heuristic; // Return the heuristic value if the node is already solved
    }

    if (node.children.empty())
    {
        node.solved = true; // Mark leaf nodes as solved
        return node.heuristic;
    }

    int minCost = numeric_limits<int>::max();
    vector<string> bestChildPath;

    for (auto &child : node.children)
    {
        vector<string> tempPath;
        int cost = child.second; // Cost of the edge

        // Process all child nodes in the AND/OR group
        for (const auto &childName : child.first)
        {
            tempPath.push_back(childName);
            cost += aostar(graph, childName, tempPath); // Add the cost recursively
        }

        if (cost < minCost)
        {
            minCost = cost;
            bestChildPath = tempPath; // Update the best path
        }
    }

    node.heuristic = minCost; // Update the heuristic of the current node
    node.solved = true;       // Mark the node as solved

    path.push_back(nodeName);                                            // Add current node to the path
    path.insert(path.end(), bestChildPath.begin(), bestChildPath.end()); // Append the best child path
    return node.heuristic;
}

int main()
{
    unordered_map<string, Node> graph;

    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the node names and their heuristic values:" << endl;
    for (int i = 0; i < n; i++)
    {
        string name;
        int heuristic;
        cin >> name >> heuristic;
        graph[name] = Node{name, heuristic};
    }

    int edges;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges in the format (parent child1,child2,... cost type(AND/OR)):" << endl;
    for (int i = 0; i < edges; i++)
    {
        string parent, childList, type;
        int cost;
        cin >> parent >> childList >> cost >> type;

        vector<string> children;
        size_t pos = 0;
        while ((pos = childList.find(',')) != string::npos)
        {
            children.push_back(childList.substr(0, pos));
            childList.erase(0, pos + 1);
        }
        children.push_back(childList); // Add the last child

        graph[parent].children.push_back({children, cost});
    }

    string start;
    cout << "Enter the start node: ";
    cin >> start;

    vector<string> path;
    int cost = aostar(graph, start, path);

    cout << "Optimal Cost: " << cost << endl;
    printPath(path);

    return 0;
}
