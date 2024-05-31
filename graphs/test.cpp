#include "dwyer.cpp"
#include "edmonds_karp.cpp"
#include "floyd_warshall.cpp"
#include "bipartite.cpp"

#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>

void test_dwyer() {
    int root = 6;
    std::vector<node> V = {
            {0, 0},
            {3, 2},
            {0, 0},
            {0, 0},
            {5, 7},
            {0, 0},
            {1, 4},
            {0, 0}
    };
    auto traverse = dwyer(V, root);
    std::vector<int> traverse_ok = {6, 1, 3, 1, 2, 1, 6, 4, 5, 4, 7, 4, 6};
    assert(traverse == traverse_ok);
    std::cout << "Dwyer traverse test: OK" << std::endl;
}

void test_edmonds_karp() {
    int n = 6;
    std::vector<std::vector<Edge>> adj(n);
    std::vector<std::tuple<int, int, int>> E = {
            {0, 1, 1},      // {u, v, c} - edge from u to v with capacity c
            {0, 2, 3},
            {0, 3, 3},
            {1, 4, 1},
            {2, 3, 2},
            {2, 4, 1},
            {3, 5, 4},
            {4, 5, 2}
    };
    for (auto t : E) {
        int u = get<0>(t), v = get<1>(t), capacity = get<2>(t);
        adj[u].push_back({v, capacity, 0, static_cast<int>(adj[v].size())});
        adj[v].push_back({u, 0, 0, static_cast<int>(adj[u].size())-1});
    }
    assert(edmondskarp(n, 0, n-1, adj) == 6);
    std::cout << "Edmond-Karp test: OK" << std::endl;
}

void test_floyd_warshall() {
    std::vector<std::vector<int>> dist = {
            {0, 117, 360, INT_MAX},
            {117, 0, 182, INT_MAX},
            {360, 182, 0, 342},
            {INT_MAX, INT_MAX, 342, 0}
    };
    floyd_warshall(dist);
    std::vector<std::vector<int>> min_dist = {
            {0, 117, 299, 641},
            {117, 0, 182, 524},
            {299, 182, 0, 342},
            {641, 524, 342, 0}
    };
    assert(min_dist == dist);
    std::cout << "Floyd-Warshall test: OK" << std::endl;
}

void test_bipartite() {
    std::vector<std::vector<int>> graph0 = {
            {1, 2},
            {0, 2},
            {0, 1}
    };
    assert(is_bipartite(graph0) == false);
    std::vector<std::vector<int>> graph1 = {
            {1, 2},
            {0, 3},
            {0},
            {1}
    };
    assert(is_bipartite(graph1) == true);
    std::cout << "Bipartite test: OK" << std::endl;
}

int main() {
    test_dwyer();
    test_edmonds_karp();
    test_floyd_warshall();
    test_bipartite();
    return 0;
}