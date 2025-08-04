#include <iostream>
#include <climits>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

void get_potentials(vector<int> &, vector<vector<pair<int, int>>> &);
void bfs(int src, vector<int> &, vector<vector<pair<int, int>>> &);

vector<vector<int>> dijkstra(vector<vector<pair<int, int>>> & adj) {
    int n = static_cast<int>(adj.size());
    vector<vector<int>> dist(n);
    vector<int> phi;
    get_potentials(phi, adj);
    for (int u = 0; u < n; u++) {
        for (auto & p : adj[u]) {
            int v = p.first;
            p.second += phi[u] - phi[v];
        }
    }
    for (int i = 0; i < n; i++) {
        bfs(i, dist[i], adj);
    }
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            dist[u][v] -= phi[u] - phi[v];
        }
    }
    return dist;
}

void bfs(int src, vector<int> & dist, vector<vector<pair<int, int>>> & adj) {
    int n = static_cast<int>(adj.size());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
    dist.resize(n, INT_MAX);
    Q.push({0, src});
    dist[src] = 0;
    while (!Q.empty()) {
        auto p = Q.top();
        Q.pop();
        int u = p.second, d = p.first;
        if (dist[u] != INT_MAX && d != dist[u]) continue;
        for (auto q : adj[u]) {
            int v = q.first, w = q.second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                Q.push({dist[v], v});
            }
        }
    }
}

void get_potentials(vector<int> & phi, vector<vector<pair<int, int>>> & adj) {
    int n = static_cast<int>(adj.size());
    phi.resize(n, 0);
    for (int i = 0; i < n-1; i++) {
        for (int u = 0; u < n; u++) {
            for (auto p : adj[u]) {
                int v = p.first, w = p.second;
                phi[v] = min(phi[v], phi[u] + w);
            }
        }
    }
}
