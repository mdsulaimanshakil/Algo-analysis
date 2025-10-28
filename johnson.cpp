#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL<<60);

int main() {
    // Example graph (0 means no edge)
    // You can change this matrix to test other graphs.
    vector<vector<int>> graph = {
        {0, -5, 2, 3},
        {0, 0, 4, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };

    int V = graph.size();

    // Build edge list: (u, v, w) for non-zero entries
    vector<array<int,3>> edges;
    for (int u = 0; u < V; ++u)
        for (int v = 0; v < V; ++v)
            if (graph[u][v] != 0)
                edges.push_back({u, v, graph[u][v]});

    // --- Bellman-Ford from new vertex s = V to compute potentials h[]
    // dist size = V + 1 (extra node)
    vector<ll> h(V+1, INF);
    h[V] = 0; // new source

    // edges_with_extra: copy original edges then add (s -> i, 0) edges
    vector<array<int,3>> edges_with_extra = edges;
    for (int i = 0; i < V; ++i) edges_with_extra.push_back({V, i, 0});

    // Relax |V| times (since total vertices = V+1)
    for (int i = 0; i < V; ++i) {
        for (auto &e : edges_with_extra) {
            int u = e[0], v = e[1], w = e[2];
            if (h[u] != INF && h[u] + w < h[v]) h[v] = h[u] + w;
        }
    }

    // Check for negative cycle: one more relaxation should not reduce any distance
    bool neg_cycle = false;
    for (auto &e : edges_with_extra) {
        int u = e[0], v = e[1], w = e[2];
        if (h[u] != INF && h[u] + w < h[v]) { neg_cycle = true; break; }
    }

    if (neg_cycle) {
        cout << "Graph contains a negative weight cycle. Johnson's algorithm cannot proceed.\n";
        return 0;
    }

    // h[0..V-1] are potentials
    // --- Reweight edges: w' = w + h[u] - h[v]  (these will be >= 0)
    vector<vector<ll>> reweight(V, vector<ll>(V, 0));
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != 0) {
                reweight[u][v] = (ll)graph[u][v] + h[u] - h[v];
                // Should be non-negative if no negative cycles
                if (reweight[u][v] < 0) reweight[u][v] = 0; // safety fallback
            }
        }
    }

    // Print reweighted graph (optional)
    cout << "Reweighted graph (0 means no edge):\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) cout << reweight[i][j] << " ";
        cout << "\n";
    }

    // --- For each source, run Dijkstra on reweighted graph and convert distances back
    for (int src = 0; src < V; ++src) {
        // Dijkstra
        vector<ll> dist(V, INF);
        dist[src] = 0;
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (int v = 0; v < V; ++v) {
                if (graph[u][v] == 0) continue; // no edge
                ll w = reweight[u][v];
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        // Convert back to original distances: d_orig[v] = dist[v] - h[src] + h[v]
        cout << "\nShortest distances from vertex " << src << ":\n";
        for (int v = 0; v < V; ++v) {
            if (dist[v] == INF) {
                cout << "Vertex " << v << ": INF\n";
            } else {
                ll d_orig = dist[v] - h[src] + h[v];
                cout << "Vertex " << v << ": " << d_orig << "\n";
            }
        }
    }

    return 0;
}
