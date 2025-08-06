/**
 * The Dijkstra's algorithm to compute distances from the source to all vertices
 * in weighted graph without negative edges.
 * Time complexity: O(n*log n + n)
 * n = |V|, m = |E|
 */

#include <climits>
#include <unordered_map>
#include <vector>
#include <queue>

#ifndef ALGORITHMS_DIJKSTRA_H
#define ALGORITHMS_DIJKSTRA_H

void dijkstra(int src, const std::vector<std::vector<std::pair<int, int>>> & adj, std::vector<int> & dist) {
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

#endif // ALGORITHMS_DIJKSTRA_H