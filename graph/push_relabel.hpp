/**
 * Push-relabel algorithm to find max flow value.
 * Some additional heuristics are used in the implementation
 * including potential initialisation using BFS and global relabel
 * procedure repeated each 10000 iterations in discharge procedure.
 * Time complexity: O(|V|^2 * |E|)
 * Space complexity: O(|V| + |E|)
 */

#include <vector>
#include <climits>
#include <queue>

#ifndef ALGORITHMS_PUSH_RELABEL_H
#define ALGORITHMS_PUSH_RELABEL_H

struct Edge {
    int v;
    int c;
    int f;
    int rev;
};

void global_relabel(std::vector<int> &, std::vector<std::vector<Edge>> &);
void push(int, Edge &, std::vector<int> &, std::vector<std::vector<Edge>> &);
void relabel(int, std::vector<int> &, std::vector<std::vector<Edge>> &);
void discharge(int, std::vector<int> &, std::vector<int> &, std::vector<int> &, std::vector<std::vector<Edge>> &);

int n, m, s, t;
int counter;
std::queue<int> overflowed;


/**
 * Find maximum flow in the network
 * @param adj       adjacency list
 * @return          max flow value
 */
int push_relabel(std::vector<std::vector<Edge>> & adj) {
    std::vector<int> excess(n + 1, 0);
    excess[s] = INT_MAX;
    std::vector<int> last(n + 1, 0);
    std::vector<int> height(n + 1);

    global_relabel(height, adj);
    for (auto &e : adj[s]) {
        int v = e.v;
        e.f = e.c;
        int f = e.f;
        excess[v] += f;
        adj[v][e.rev].f = -f;
        overflowed.push(v);
    }

    while (!overflowed.empty()) {
        int u = overflowed.front();
        overflowed.pop();
        if (u != t && height[u] != INT_MAX) {
            discharge(u, excess, height, last, adj);
        }
        if (counter >= 10000) {
            global_relabel(height, adj);
            fill(last.begin(), last.end(), 0);
            counter = 0;
        }
    }
    return excess[t];
}

/**
 * Reinitialise all labels
 * @param height        potentials
 * @param adj           adjacency list
 */
void global_relabel(std::vector<int> & height, std::vector<std::vector<Edge>> & adj) {
    std::fill(height.begin(), height.end(), INT_MAX);
    std::queue<std::pair<int, int>> q;
    q.emplace(t, 0);
    height[t] = 0;
    height[s] = n;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int u = p.first;
        int dist = p.second;
        for (auto e : adj[u]) {
            int v = e.v;
            auto rev_e = adj[v][e.rev];
            if (height[v] != INT_MAX || rev_e.c <= rev_e.f) {
                continue;
            }
            height[v] = dist + 1;
            q.emplace(v, dist + 1);
        }
    }
}

/**
 * Push the excessive charge - as much as possible
 * @param u             vertex to push the excess from
 * @param e             edge to push the excess through
 * @param excess        excessive flow values for all vertices
 * @param adj           adjacency list
 */
void push(int u, Edge & e, std::vector<int> & excess, std::vector<std::vector<Edge>> & adj) {
    int v = e.v, rev = e.rev;
    int c = e.c, f = e.f;
    if (c <= f) {
        return;
    }
    int min_f = std::min(excess[u], c - f);
    excess[u] -= min_f;
    if (v != s) {
        excess[v] += min_f;
    }
    e.f += min_f;
    adj[v][rev].f -= min_f;
    if (v != s && v != t && min_f > 0 && excess[v] == min_f) {
        overflowed.push(v);
    }
}

/**
 * Relabel the vertex
 * @param u             vertex to be relabeled
 * @param height        potentials
 * @param adj           adjacency list
 */
void relabel(int u, std::vector<int> & height, std::vector<std::vector<Edge>> & adj) {
    int h = INT_MAX;
    for (auto e : adj[u]) {
        if (e.c > e.f) {
            h = std::min(h, height[e.v]);
        }
    }
    if (h < INT_MAX) {
        height[u] = h + 1;
    }
}

/**
 * Discharge the vertex with excessive charge
 * @param u             vertex to discharge
 * @param excess        excessive flow values for all vertices
 * @param height        potentials
 * @param last          last vertex that the charge was pushed to from u
 * @param adj           adjacency list
 */
void discharge(int u, std::vector<int> & excess, std::vector<int> & height, std::vector<int> & last, std::vector<std::vector<Edge>> & adj) {
    int i = last[u], n_adj = static_cast<int>(adj[u].size());
    while (excess[u] > 0) {
        int hu = height[u];
        for (; i < n_adj; i++, counter++) {
            auto &e = adj[u][i];
            int hv = height[e.v];
            if (hv == INT_MAX || hu != hv + 1) {
                continue;
            }
            push(u, e, excess, adj);
            if (excess[u] == 0) {
                last[u] = i;
                return;
            }
        }
        relabel(u, height, adj);
        i = 0;
    }
}

#endif // ALGORITHMS_PUSH_RELABEL_H