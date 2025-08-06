/**
 * Implementation of the Bellman-Ford algorithm to find the shortest paths
 * from a single source to all other vertices in a weighted graph.
 * The algorithm can handle graph with negative weights and it detects
 * negative weight cycles.
 * Time complexity: O(n*m)
 * Space complexity: O(n)
 * n = |V|, m = |E|
 */

#include <vector>
#include <climits>
#include <iostream>

#ifndef ALGORITHMS_BELLMAN_H
#define ALGORITHMS_BELLMAN_H

/**
 * Compute the shortest distances from src to other vertices
 * @param src       source vertex
 * @param adj       adjacency list
 * @param dist      array of distances
 * @return          True if a negative weight cycle is detected, otherwise false.
 */
bool bellman_ford(int src, const std::vector<std::vector<std::pair<int, int>>> &adj, std::vector<int> & dist) {
    int n = static_cast<int>(adj.size());
    dist.resize(n, INT_MAX);
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (auto p : adj[u]) {
                int v = p.first, weight = p.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (auto p : adj[u]) {
            int v = p.first, weight = p.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist.clear();
                return true;
            }
        }
    }
    return false;
}

#endif // ALGORITHMS_BELLMAN_H