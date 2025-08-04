/**
 * Implementation of Edmonds-Karp's algorithm for finding maximum
 * flow in a network. The algorithm uses the Ford-Fulkerson method
 * but chooses the shortest augmenting paths thanks to BFS.
 * Time complexity: O(|V|*|E|^2)
 * Space complexity: O(|V|+|E|)
 * Created on 01.03.2024
 */

#include <vector>
#include <climits>
#include <queue>

struct Edge {
    int v, c, f, rev_idx;
};
struct PathEdge {
    int u = -1, v{}, min_f = INT_MAX, idx{}, rev_idx{};
};

/**
 * Find the shortest augmenting path
 * @param n             number of vertices
 * @param s             source
 * @param t             sink
 * @param prev_min      previous edge ont the path to the vertex
 * @param adj           adjacency list
 * @return              minimum flow on the augmenting path from s to t
 */
int bfs(int n, int s, int t, std::vector<PathEdge> &prev_min, std::vector<std::vector<Edge>> &adj) {
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int n_adj = static_cast<int>(adj[u].size());
        for (int i = 0; i < n_adj; i++) {
            auto e = adj[u][i];
            int v = e.v;
            if (visited[v] || e.c <= e.f) {
                continue;
            }
            visited[v] = true;
            int min_f = std::min(prev_min[u].min_f, e.c - e.f);
            prev_min[v] = { u, v, min_f, i, e.rev_idx };
            q.push(v);
            if (v == t) {
                return min_f;
            }
        }
    }
    return 0;
}

/**
 * Update flow on the augmenting path
 * @param min_f         increase in flow value on the path
 * @param t             sink
 * @param prev_min      previous edge ont the path to the vertex
 * @param adj           adjacency list
 */
void flow(int min_f, int t, std::vector<PathEdge> &prev_min, std::vector<std::vector<Edge>> &adj) {
    auto e = prev_min[t];
    int u = e.u, v = e.v, idx = e.idx, rev_idx = e.rev_idx;
    while (u != -1) {
        adj[u][idx].f += min_f;
        adj[v][rev_idx].f -= min_f;
        e = prev_min[u];
        u = e.u, v = e.v, idx = e.idx, rev_idx = e.rev_idx;
    }
}

/**
 * Find maximum flow in the network
 * @param n         number of vertices
 * @param s         source
 * @param t         sink
 * @param adj       adjacency list
 * @return          value of maximum flow
 */
int edmondskarp(int n, int s, int t, std::vector<std::vector<Edge>> &adj) {
    int max_flow = 0, f;
    while (true) {
        std::vector<PathEdge> prev_min(n);
        if (!(f = bfs(n, s, t, prev_min, adj))) {
            break;
        }
        flow(f, t, prev_min, adj);
        max_flow += f;
    }
    return max_flow;
}