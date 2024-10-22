#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int start, vector<vector<int>> &adjList, vector<bool> &visited)
{
    stack<int> s;
    s.push(start);
    visited[start] = true;

    while (!s.empty())
    {
        int node = s.top();
        s.pop();
        cout << node << " ";

        for (int neighbor : adjList[node])
        {
            if (!visited[neighbor])
            {
                s.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

int main()
{
    int n, e;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> e;

    vector<vector<int>> adjList(n);
    vector<bool> visited(n, false);

    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < e; ++i)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int start;
    cout << "Enter the starting node: ";
    cin >> start;

    cout << "DFS traversal starting from node " << start << ": ";
    dfs(start, adjList, visited);
    cout << endl;

    return 0;
}