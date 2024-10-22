#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int start, vector<vector<int>> &adjList, vector<bool> &visited)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << node << " ";

                for (int neighbor : adjList[node])
        {
            if (!visited[neighbor])
            {
                q.push(neighbor);
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

    cout << "BFS traversal starting from node " << start << ": ";
    bfs(start, adjList, visited);
    cout << endl;

    return 0;
}