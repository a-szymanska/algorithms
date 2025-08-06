/**
 * The Johnson's algorithm to compute pairwise distances
 * between all pairs of vertices in weighted graph.
 * Time complexity: O(n^2*log n + n*m)
 * n = |V|, m = |E|
 */

#include <vector>

#include "bellman_ford.hpp"
#include "dijkstra.hpp"

#ifndef ALGORITHMS_JOHNSON_H
#define ALGORITHMS_JOHNSON_H

/**
 * Computed pairwise distances
 * @param adj   adjacency lists
 * @param dist  resulting distances
 */
void johnson(const std::vector<std::vector<std::pair<int, int>>> & adj, std::vector<std::vector<int>> & dist) {
    int n = static_cast<int>(adj.size());
    dist.resize(n+1);
    std::vector<std::vector<std::pair<int, int>>> adj_with_src = adj;
    adj_with_src.emplace_back(n);
    for (int i = 0; i < n; i++) {
        adj_with_src[n][i] = {1, i};
    }
    std::vector<int> phi;
    bellman_ford(n, adj_with_src, phi);
    adj_with_src.resize(n);
    for (int u = 0; u < n; u++) {
        for (auto & p: adj_with_src[u]) {
            int v = p.first;
            p.second += phi[u] - phi[v];
        }
    }
    for (int i = 0; i < n; i++) {
        dijkstra(i, adj_with_src, dist[i]);
    }
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            dist[u][v] -= phi[u] - phi[v];
        }
    }
    dist.resize(n);
}

#endif // ALGORITHMS_JOHNSON_H