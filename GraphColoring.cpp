#include <iostream>
#include <vector>
using namespace std;

void graphColoring(vector<vector<int>> &adj, int n)
{
    vector<int> color(n, -1);
    color[0] = 0;
    vector<bool> availableColors(n, false);

    for (int u = 1; u < n; u++)
    {
        for (int v : adj[u])
        {
            if (color[v] != -1)
            {
                availableColors[color[v]] = true;
            }
        }

        int cr;
        for (cr = 0; cr < n; cr++)
        {
            if (!availableColors[cr])
                break;
        }

        color[u] = cr;

        for (int v : adj[u])
        {
            if (color[v] != -1)
            {
                availableColors[color[v]] = false;
            }
        }
    }

    cout << "Vertex\tColor" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << "\t" << color[i] << endl;
    }
}

int main()
{
    int n, e;
    cin >> n >> e;
    vector<vector<int>> adj(n);
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    graphColoring(adj, n);
    return 0;
}