#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> dfs(vector<vector<int>> adj, vector<bool> vis, int start, int goal)
{
    stack<int> st;
    st.push(start);
    vis[start] = true;
    vector<int> ans;

    while (!st.empty())
    {
        int node = st.top();
        st.pop();
        ans.push_back(node);

        if (node == goal)
        {
            return ans;
        }

        for (int adjnode : adj[node])
        {
            if (!vis[adjnode])
            {
                vis[adjnode] = true;
                st.push(adjnode);
            }
        }
    }
    return ans;
}

int main()
{
    int n, e;
    cout << "Enter the number of nodes and edges:" << endl;
    cin >> n >> e;

    vector<vector<int>> adj(n);
    vector<bool> vis(n, false);

    cout << "Enter the edges:" << endl;
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start, goal;
    cout << "Enter start node: " << endl;
    cin >> start;
    cout << "Enter goal node: " << endl;
    cin >> goal;

    vector<int> ans;
    ans = dfs(adj, vis, start, goal);

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}