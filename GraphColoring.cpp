#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void graphColoring(vector<vector<int>> &adjList, int numVertices)
{
    vector<int> result(numVertices, -1);
    result[0] = 0;

    vector<bool> available(numVertices, false);

    for (int u = 1; u < numVertices; u++)
    {
        for (int i : adjList[u])
        {
            if (result[i] != -1)
            {
                available[result[i]] = true;
            }
        }

        int color;
        for (color = 0; color < numVertices; color++)
        {
            if (!available[color])
            {
                break;
            }
        }

        result[u] = color;
        fill(available.begin(), available.end(), false);
    }

    cout << "Vertex\tColor" << endl;
    for (int u = 0; u < numVertices; u++)
    {
        cout << u << "\t" << result[u] << endl;
    }
}

int main()
{
    int numVertices;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    vector<vector<int>> adjList(numVertices);

    cout << "Enter the adjacency list of the graph (enter -1 to end the list for a vertex):" << endl;
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Vertex " << i << ": ";
        int vertex;
        while (cin >> vertex && vertex != -1)
        {
            adjList[i].push_back(vertex);
        }
    }

    graphColoring(adjList, numVertices);

    return 0;
}

/*
Enter the number of vertices: 5
Enter the adjacency list of the graph (enter -1 to end the list for a vertex):
Vertex 0: 1 2 -1
Vertex 1: 0 2 3 -1
Vertex 2: 0 1 3 4 -1
Vertex 3: 1 2 4 -1
Vertex 4: 2 3 -1
Vertex  Color
0       0
1       1
2       2
3       0
4       1
*/