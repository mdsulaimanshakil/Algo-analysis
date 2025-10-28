#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

int main() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;
    
    // 1-indexed matrix
    vector<vector<ll>> dist(n+1, vector<ll>(n+1, INF));
    for (int i = 1; i <= n; ++i) dist[i][i] = 0;
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        // undirected: keep the minimal edge if multiple given
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }
    
    // Floyd–Warshall
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (dist[i][k] == INF) continue; // small optimization
            for (int j = 1; j <= n; ++j) {
                if (dist[k][j] == INF) continue;
                ll nd = dist[i][k] + dist[k][j];
                if (nd < dist[i][j]) dist[i][j] = nd;
            }
        }
    }
    
    // Answer queries
    while (q--) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] >= INF/2) cout << -1 << '\n';
        else cout << dist[a][b] << '\n';
    }
    return 0;
}
