/**
 * Implementation of Floyd-Warshall's algorithm for finding
 * the shortest paths between all pairs of vertices in a weighted graph.
 * Time complexity: O(|V|^3)
 * Space complexity: O(|V|^2)
 * Created on 21.11.2023
 */

#include <vector>
#include <climits>

/**
 * Find the shortest pairwise distances
 * @param dist      2D array with lengths of edges
 */
void floyd_warshall(std::vector<std::vector<int>> & dist) {
    int n = static_cast<int>(dist.size());
    for (int u = 0; u < n; u++) {
        dist[u][u] = 0;
    }
    for (int w = 0; w < n; w++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (dist[u][w] != INT_MAX && dist[w][v] != INT_MAX) {
                    dist[u][v] = std::min(dist[u][w] + dist[w][v], dist[u][v]);
                }
            }
        }
    }
}