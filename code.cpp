#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

void menu();

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
            adjList[dest].push_back(make_pair(src, weight));
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

    void printApplication() const {
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

    // ---------------- DFS ----------------
    void DFSUtil(int v, vector<bool> &visited) const {
        visited[v] = true;
        cout << "Inspecting Tower " << v << endl;

        for (const auto &adj : adjList[v]) {
            int nxt = adj.first;
            if (!visited[nxt]) DFSUtil(nxt, visited);
        }
    }

     void DFS(int start) const {
        cout << "\nSignal Path Trace (DFS) starting from Tower " << start << ":\n";
        cout << "Purpose: Trace how emergency signal spreads\n";
        cout << "=======================================\n";
        vector<bool> visited(SIZE, false);
        DFSUtil(start, visited);
        cout << endl;
    }

    // ---------------- BFS ----------------
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

    vector<long long> dijkstra(int start) const {
        const long long INF = numeric_limits<long long>::max() / 4;
        vector<long long> dist(SIZE, INF);
        // min-heap of (distance, vertex)
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue; // stale entry
            for (const auto &edge : adjList[u]) {
                int v = edge.first;
                long long w = edge.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    void printShortestPathsFrom(int start) const {
        auto dist = dijkstra(start);
        cout << "\nShortest path from node " << start << ":\n";
        for (int i = 0; i < SIZE; ++i) {
            cout << start << " -> " << i << " : ";
            if (dist[i] >= (numeric_limits<long long>::max() / 8)) cout << "INF";
            else cout << dist[i];
            cout << "\n";
        }
        cout << endl;
    }

    void MSTPrim(int start=0) {
        vector<bool> visited(SIZE,false);
        visited[start] = true;
        int edgesUsed = 0;

        cout << "Minimum Spanning Tree edges:\n";

        while(edgesUsed < SIZE-1){
            int minWeight = numeric_limits<int>::max();
            int u = -1, v = -1;
            for(int i=0;i<SIZE;i++){
                if(!visited[i]) continue;
                for(auto &p: adjList[i]){
                    if(!visited[p.first] && p.second < minWeight){
                        minWeight = p.second;
                        u = i;
                        v = p.first;
                    }
                }
            }
            if(u != -1 && v != -1){
                cout << "Edge from " << u << " to " << v 
                     << " with capacity: " << minWeight << " units\n";
                visited[v] = true;
                edgesUsed++;
            } else break;
        }
    }
};

int main() {
    int choice;
    vector<Edge> edges = {
        {0,2,14},{0,1,12},{0,3,4},
        {2,3,6},{1,7,15},{1,5,7},
        {4,5,9},{2,4,4},{2,5,5},
        {8,5,4},{8,3,9},{8,6,13},
        {6,2,12},{6,5,7},{7,2,5}
    };

    Graph graph(edges);

    while (choice != 0) {
        menu();
        cout << "Enter choice: " << endl;
        cin >> choice;
        if (choice == 1) {

        } else if (choice == 2) {

        } else if (choice == 3) {

        } else if (choice == 4) {

        } else if (choice == 5) {
            
        }
    }

    graph.printApplication();
    graph.DFS(0);
    graph.BFS(0);
    graph.printShortestPathsFrom(0);
    graph.MSTPrim();
    return 0;
}

//Prints menu
void menu() {
    cout << "Emergency Response Radio Network Menu:" << endl;
    cout << "\n[1] Display radio network" << "\n[2] Trace signal propagation (BFS)" << "\n[3] Plan signal inspection route (DFS)" << "\nCalculate shortest paths from a tower" << "\n[5] Calculate minimum spanning tree of network" << "[0] Exit" << endl;
}