#include <climits>
#include <unordered_map>
#include <vector>
#include <queue>


void dijkstra(int src, std::vector<std::vector<std::pair<int, int>>> & adj, std::vector<int> & dist) {
    int n = static_cast<int>(adj.size());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> Q;

    dist.resize(n, INT_MAX);
    Q.emplace(0, src);
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
                Q.emplace(dist[v], v);
            }
        }
    }
}