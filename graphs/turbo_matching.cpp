/**
 * Implementation of the Turbo Matching algorithm to find
 * the maximum matching in a bipartite graph by iteratively
 * augmenting paths using DFS.
 * Time complexity: O(V*E)
 * Space complexity: O(V+E)
 * Created by Anna Szymańska on 14.01.2024
 */

#include <vector>
#include <functional>

/**
 * Find the maximum match in bipartite graph
 * @param adj       adjacency list
 * @return          size of the maximum match
 */
int find_match(std::vector<std::vector<int>>& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<int> M(2 * n + 1, -1);
    bool found;
    do {
        std::vector<bool> vis(2 * n + 1, false);
        found = false;
        std::function<bool(int)> dfs = [&](int u) -> bool {
            if (vis[u]) return false;
            vis[u] = true;
            for (auto v : adj[u]) {
                if (M[v] == -1 || dfs(M[v])) {
                    M[u] = v;
                    M[v] = u;
                    return true;
                }
            }
            return false;
        };

        for (int u = 1; u <= n; u++) {
            if (M[u] == -1) {
                found = std::max(found, dfs(u));
            }
        }
    } while (found);

    int n_matched = 0;
    for (int i = 1; i <= n; i++) {
        if (M[i] != -1) n_matched++;
    }
    return n_matched / 2;
}