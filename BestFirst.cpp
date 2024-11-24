#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void reconstructPath(vector<int> parent, int goal)
{
    int curr = goal;
    vector<int> path;
    while (curr != -1)
    {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i] << " ";
    }
}

void bfs(vector<vector<int>> adj, vector<int> h, int start, int goal, int n)
{
    vector<bool> vis(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({h[0], start});
    vector<int> parent(n, -1);
    vis[start] = true;

    while (!pq.empty())
    {
        int node = pq.top().second;
        int est = pq.top().first;
        pq.pop();

        if (node == goal)
        {
            reconstructPath(parent, goal);
        }

        for (int adjnode : adj[node])
        {
            if (!vis[adjnode])
            {
                vis[adjnode] = true;
                parent[adjnode] = node;
                pq.push({h[adjnode], adjnode});
            }
        }
    }
}

int main()
{
    int n, e;
    cout << "Enter the number of nodes and edges" << endl;
    cin >> n >> e;

    vector<vector<int>> adj(n);

    cout << "Enter the edges" << endl;
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> h(n);

    cout << "Enter the heuristic values of the nodes" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    int start, goal;

    cout << "Enter start node" << endl;
    cin >> start;
    cout << "Enter goal node" << endl;
    cin >> goal;

    bfs(adj, h, start, goal, n);

    return 0;
}