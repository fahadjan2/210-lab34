#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 9;

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

    void printApplication() const { // done by LLM
        cout << "Emergency Response Radio Network Map\n";
        cout << "=======================================\n\n";

        const char* names[SIZE] = {
            "Central Command",
            "North Relay Station",
            "East Relay Hub",
            "Industrial District Tower",
            "Airport Tower",
            "Medical Center Tower",
            "Southwest Relay Station",
            "University Tower",
            "Mountain Ridge Tower"
        };

        for (int i = 0; i < SIZE; i++) {
            cout << "Tower " << i << " (" << names[i] << ") connects to:\n";
            for (const auto &p : adjList[i]) {
                cout << "  → Tower " << p.first
                     << " (" << names[p.first]
                     << ") - Signal Strength: " << p.second << " dBm\n";
            }
            cout << endl;
        }
    }

    // ---------------- DFS ---------------- done by LLM
    void DFSUtil(int v, vector<bool> &visited) const {
        visited[v] = true;
        cout << "Inspecting Tower " << v << endl;

        for (const auto &adj : adjList[v]) {
            int nxt = adj.first;
            if (!visited[nxt]) DFSUtil(nxt, visited);
        }
    }

     void DFS(int start) const { //done by LLM
        cout << "\nSignal Path Trace (DFS) starting from Tower " << start << ":\n";
        cout << "Purpose: Trace how emergency signal spreads\n";
        cout << "=======================================\n";
        vector<bool> visited(SIZE, false);
        DFSUtil(start, visited);
        cout << endl;
    }

    // ---------------- BFS ---------------- done by LLM
     void BFS(int start) const {
        cout << "\nCoverage Radius Scan (BFS) starting from Tower " << start << ":\n";
        cout << "Purpose: Identify signal reach by distance\n";
        cout << "=======================================\n";

        vector<bool> visited(SIZE, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            cout << "Checking Tower " << v << endl;

            for (const auto &adj : adjList[v]) {
                int nxt = adj.first;
                if (!visited[nxt]) {
                    visited[nxt] = true;
                    q.push(nxt);
                }
            }
        }
        cout << endl;
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

    graph.printApplication();
    graph.DFS(0);
    graph.BFS(0);

    cout << endl;

    return 0;
}