#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 11;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));  // undirected
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // ---------------- DFS ---------------- done by LLM
    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto &adj : adjList[v]) {
            int next = adj.first;
            if (!visited[next])
                DFSUtil(next, visited);
        }
    }

    void DFS(int start) { // done by LLM
        vector<bool> visited(SIZE, false);
        DFSUtil(start, visited);
    }

    // ---------------- BFS ---------------- done by LLM
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto &adj : adjList[v]) {
                int next = adj.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
    }
};

int main() {
    vector<Edge> edges = {
        {0,2,14},{0,1,12},{0,3,4},
        {2,3,6},{1,7,15},{1,5,7},
        {4,5,9},{2,4,4},{2,5,5},
        {8,5,4},{8,3,9},{8,6,13},
        {6,2,12},{6,5,7},{7,2,5}
    };

    Graph graph(edges);

    graph.printGraph();

    cout << "DFS starting from vertex 0:" << endl;
    graph.DFS(0);
    cout << endl;

    cout << "BFS starting from vertex 0:" << endl;
    graph.BFS(0);
    cout << endl;

    return 0;
}