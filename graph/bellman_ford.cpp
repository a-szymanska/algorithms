/**
 * Implementation of the Bellman-Ford algorithm to find the shortest paths
 * from a single source to all other vertices in a weighted graph.
 * The algorithm can handle graph with negative weights and it detects
 * negative weight cycles.
 * Time complexity: O(V*E)
 * Space complexity: O(V)
 * Created on 11.10.2023
 */

#include <vector>
#include <iostream>


/**
 * Compute the shortest distances from src to other vertices
 * @param adj       adjacency list
 * @param src       source vertex
 * @return          array of distances
 *                  If a negative weight cycle is detected, an empty vector is returned.
 */
std::vector<int> bellman_ford(const std::vector<std::vector<std::pair<int, int>>> &adj, int src) {
    int n = static_cast<int>(adj.size());
    std::vector<int> dist(n, INT_MAX);
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
                return {};
            }
        }
    }
    return dist;
}