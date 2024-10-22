#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

#define MAX 20

struct Node
{
    int id;
    int cost;
    bool isAndNode;
    vector<int> children;
};

int AOStar(int node, vector<Node> &graph, vector<int> &solution)
{
    if (graph[node].children.empty())
    {
        solution.push_back(node);
        return graph[node].cost;
    }

    int minCost = INT_MAX;

    if (graph[node].isAndNode)
    {
        int cost1 = AOStar(graph[node].children[0], graph, solution);
        int cost2 = AOStar(graph[node].children[1], graph, solution);
        minCost = cost1 + cost2;
        solution.push_back(node);
    }
    else
    {
        int bestChild = -1;
        for (int child : graph[node].children)
        {
            vector<int> tempSolution;
            int cost = AOStar(child, graph, tempSolution);
            if (cost < minCost)
            {
                minCost = cost;
                bestChild = child;
                solution = tempSolution;
            }
        }
        solution.push_back(node);
    }

    return minCost;
}

int main()
{
    int n;
    cout << "Enter the number of nodes in the AND-OR graph: ";
    cin >> n;

    vector<Node> graph(n);
    vector<int> solution;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter details for node " << i << ":\n";
        graph[i].id = i;

        cout << "Cost (heuristic value): ";
        cin >> graph[i].cost;

        char nodeType;
        cout << "Is this node an AND node (enter 'Y' for yes, 'N' for no): ";
        cin >> nodeType;
        graph[i].isAndNode = (nodeType == 'Y' || nodeType == 'y');

        int numChildren;
        cout << "Number of children: ";
        cin >> numChildren;
        graph[i].children.resize(numChildren);

        for (int j = 0; j < numChildren; j++)
        {
            cout << "Enter child " << j + 1 << " for node " << i << ": ";
            cin >> graph[i].children[j];
        }
    }

    int startNode = 0;
    cout << "Enter the start node (root node): ";
    cin >> startNode;

    int result = AOStar(startNode, graph, solution);

    cout << "Optimal Solution Path: \n";
    for (auto it = solution.rbegin(); it != solution.rend(); ++it)
    {
        cout << "Node " << *it << " -> ";
    }
    cout << "END\n";
    cout << "Total Cost: " << result << endl;

    return 0;
}

/*

Enter the number of nodes in the AND-OR graph: 7
Enter details for node 0:
Cost (heuristic value): 0
Is this node an AND node (enter 'Y' for yes, 'N' for no): N
Number of children: 2
Enter child 1 for node 0: 1
Enter child 2 for node 0: 2
Enter details for node 1:
Cost (heuristic value): 1
Is this node an AND node (enter 'Y' for yes, 'N' for no): Y
Number of children: 2
Enter child 1 for node 1: 3
Enter child 2 for node 1: 4
Enter details for node 2:
Cost (heuristic value): 2
Is this node an AND node (enter 'Y' for yes, 'N' for no): Y
Number of children: 2
Enter child 1 for node 2: 5
Enter child 2 for node 2: 6
Enter details for node 3:
Cost (heuristic value): 3
Is this node an AND node (enter 'Y' for yes, 'N' for no): N
Number of children: 0
Enter details for node 4:
Cost (heuristic value): 4
Is this node an AND node (enter 'Y' for yes, 'N' for no): N
Number of children: 0
Enter details for node 5:
Cost (heuristic value): 5
Is this node an AND node (enter 'Y' for yes, 'N' for no): N
Number of children: 0
Enter details for node 6:
Cost (heuristic value): 6
Is this node an AND node (enter 'Y' for yes, 'N' for no): N
Number of children: 0
Enter the start node (root node): 0
Optimal Solution Path:
Node 0 -> Node 1 -> Node 4 -> Node 3 -> END
Total Cost: 8

*/
