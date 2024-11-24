#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

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
    cout << "Path: ";
    for (int node : path)
    {
        cout << node << " ";
    }
    cout << endl;
}

void astar(vector<vector<pair<int, int>>> &adj, vector<int> &h, int start, int goal, int n)
{
    vector<int> g(n, INT_MAX);
    vector<bool> vis(n, false);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    g[start] = 0;
    pq.push({h[start], start});

    while (!pq.empty())
    {
        int node = pq.top().second;
        int f = pq.top().first;
        pq.pop();

        if (vis[node])
            continue;
        vis[node] = true;

        if (node == goal)
        {
            cout << "Total cost: " << g[goal] << endl;
            reconstructPath(parent, goal);
            return;
        }

        for (auto &neighbor : adj[node])
        {
            int adjnode = neighbor.first;
            int weight = neighbor.second;

            if (!vis[adjnode] && g[node] + weight < g[adjnode])
            {
                g[adjnode] = g[node] + weight;
                parent[adjnode] = node;
                pq.push({g[adjnode] + h[adjnode], adjnode});
            }
        }
    }

    cout << "No path exists from " << start << " to " << goal << endl;
}

int main()
{
    int n, e;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> e;

    vector<vector<pair<int, int>>> adj(n);

    cout << "Enter the edges (u, v, weight):" << endl;
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> h(n);
    cout << "Enter the heuristic values of the nodes:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    int start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    astar(adj, h, start, goal, n);

    return 0;
}