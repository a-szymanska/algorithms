/**
 * Algorithm to check if graph is bipartite using BFS.
 * The algorithm traverses the graph and colors it using two colors.
 * If it finds a conflict in coloring, the graph is not bipartite.
 * Time complexity: O(n + m)
 * Space complexity: O(n)
 * n = |V|, m = |E|
 */

#include <vector>
#include <queue>


#ifndef ALGORITHMS_BIPARTITE_H
#define ALGORITHMS_BIPARTITE_H

/**
 * Check if a graph is bipartite
 * @param adj       adjacency list
 * @return          true if the graph is bipartite else false
 */
bool is_bipartite(std::vector<std::vector<int>> & adj) {
    int n = static_cast<int>(adj.size());
    std::vector<int> colour(n, false);
    std::queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (colour[i] != 0)  {
            continue;
        }
        colour[i] = 1;
        Q.push(i);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int v : adj[u]) {
                if (colour[v] == 0) {
                    Q.push(v);
                    colour[v] = -colour[u];
                } else if (colour[v] == colour[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}


#endif // ALGORITHMS_BIPARTITE_H