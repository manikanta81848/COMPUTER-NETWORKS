#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii; // pair of (distance, node index)

const int INF = numeric_limits<int>::max(); // infinite distance

vector<vector<pii>> adjList; // adjacency list
vector<int> dist; // shortest distance from source
vector<bool> visited; // visited nodes

void dijkstra(int source) {
    dist.assign(adjList.size(), INF); // initialize all distances to INF
    visited.assign(adjList.size(), false); // initialize all nodes as unvisited

    priority_queue<pii, vector<pii>, greater<pii>> pq; // min-heap priority queue
    pq.push({0, source}); // push source with distance 0
    dist[source] = 0; // set source distance to 0

    while (!pq.empty()) {
        int u = pq.top().second; // get node with smallest distance
        pq.pop();

        if (visited[u]) continue; // ignore visited nodes

        visited[u] = true; // mark node as visited

        for (auto item : adjList[u]) {
            int v = item.first;
            int w = item.second;
            // relaxation step: update distance to neighboring node
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v}); // push updated distance to priority queue
            }
        }
    }
}

int main() {
    int n, m, source;
    cin >> n >> m >> source;

    adjList.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w}); // add edge from u to v with weight w
    }

    dijkstra(source);

    for (int i = 0; i < n; i++) {
        cout<<source<<" --> "<<source+i << " : ";
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << endl;
    }
    return 0;
}
