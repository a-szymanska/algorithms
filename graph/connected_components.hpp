/**
 * Implementation of the Kosaraju's algorithm
 * for strongly connected components in a graph.
 * Time complexity: O(n + m)
 * Space complexity: O(n + m)
 * n = |V|, m = |E|
 */

#include <vector>
#include <functional>

#ifndef ALGORITHMS_CONNECTED_H
#define ALGORITHMS_CONNECTED_H

/**
 * Determin strongly connected components for a given graph
 * @param n         number of vertices
 * @param adj       adjacency list
 * @return          component number for each vertex
 */
std::vector<int> get_scc(int n, const std::vector<std::vector<int>> & adj) {
    std::vector<int> order;
    std::vector<bool> visited(n, false);
    std::function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (auto y : adj[u]) {
            if (!visited[y]) {
                dfs(y);
            }
        }
        order.push_back(u);
    };
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    std::vector<std::vector<int>> rev_adj(n);
    std::vector<int> component(n, -1);
    for (int u = 0; u < n; u++) {
        for (auto v: adj[u]) {
            rev_adj[v].push_back(u);
        }
    }
    int comp = 0;
    std::function<void(int)> rev_dfs = [&](int x) {
        component[x] = comp;
        for (auto y : rev_adj[x]) {
            if (component[y] == -1) {
                rev_dfs(y);
            }
        }
    };
    while (!order.empty()) {
        int x = order.back();
        order.pop_back();
        if (component[x] == -1) {
            rev_dfs(x);
            comp++;
        }
    }
    return component;
}

#endif // ALGORITHMS_CONNECTED_H