/**
 * Topological sort algorithm using BFS.
 * Time complexity: O(n + m)
 * Space complexity: O(n)
 * Created on 30.04.2023
 */
#include <vector>
#include <queue>

/**
 * Sort vertices in topological order
 * @param sorted        arrays of arrays corresponding to layers
 * @param adj           adjacency list
 * @return              true if the graph is DAG else false
 *                      (topological sorting not possible)
 */
bool toposort(std::vector<std::vector<int>> & sorted, const std::vector<std::vector<int>> & adj) {
    int n = static_cast<int>(adj.size());
    std::vector<int> deg(n, 0);
    for (int x = 0; x < n; x++) {
        for (auto y : adj[x]) {
            deg[y]++;
        }
    }
    std::queue<std::pair<int, int>> Q;
    for (int x = 0; x < n; x++) {
        if (deg[x] == 0) {
            Q.emplace(x, 0);
        }
    }
    int visit_counter = 0, last_layer = 0;
    std::vector<int> sorted_tmp;
    while (!Q.empty()) {
        int x = Q.front().first, layer = Q.front().second;
        Q.pop();
        if (layer != last_layer) {
            sorted.push_back(sorted_tmp);
            sorted_tmp.clear();
            last_layer = layer;
        }
        sorted_tmp.push_back(x);
        for (int y : adj[x]) {
            if (--deg[y] == 0) {
                Q.emplace(y, layer + 1);
            }
        }
        visit_counter++;
    }
    sorted.push_back(sorted_tmp);
    return visit_counter == n;
}
