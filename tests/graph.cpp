#include "../graph/dwyer.hpp"
#include "../graph/edmonds_karp.hpp"
#include "../graph/floyd_warshall.hpp"
#include "../graph/bipartite.hpp"
#include "../graph/turbo_matching.hpp"
#include "../graph/bellman_ford.hpp"
#include "../graph/dijkstra.hpp"
#include "../graph/johnson.hpp"
#include "../graph/tree_hashing.hpp"
#include "../graph/connected_components.hpp"
#include "../graph/topological_sort.hpp"

#include <iostream>
#include <vector>
#include <climits>
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

void test_turbo_matching() {
    std::vector<std::vector<int>> adj = {
            {4},
            {6},
            {5, 6},
            {5, 6},
            {0},
            {2, 3},
            {1, 2, 3}
    };
    assert(find_match(adj) == 3);
    std::cout << "Turbo matching test: OK" << std::endl;
}

void test_bellman_ford() {
    std::vector<std::vector<std::pair<int, int>>> adj0 = {
            {{1,-1}, {2,4}},
            {{2,3}, {3,2}, {4,2}},
            {},
            {{2,5}, {1,1}},
            {{3,-3}}
    };
    std::vector<int> dist0, dist0_ok = {0, -1, 2, -2, 1};
    bellman_ford(0, adj0, dist0);
    assert(dist0_ok == dist0);

    // Negative weight cycle
    std::vector<std::vector<std::pair<int, int>>> adj1 = {
            {{1,-1}, {2,4}},
            {{3,1}},
            {},
            {{0,-2}}
    };
    std::vector<int> dist1;
    assert(bellman_ford(0, adj1, dist1));
    std::cout << "Bellman-Ford test: OK" << std::endl;
}

void test_dijkstra() {
        std::vector<std::vector<std::pair<int, int>>> adj = {
                {{1,1}, {4,10}},
                {{0,4}, {2,2}},
                {},
                {{0,3}}
        };
        std::vector<int> dist, dist_ok = {0, 1, 3, INT_MAX};
        dijkstra(0, adj, dist);
        assert(dist_ok == dist);

    std::cout << "Dijkstra test: OK" << std::endl;
}

void test_johnson() {
    std::vector<std::vector<std::pair<int, int>>> adj = {
            {{1,3}},
            {{2,-1}, {0,4}},
            {{0,-1}}
    };
    std::vector<std::vector<int>> dist, dist_ok = {
            {0, 3, 2},
            {-2, 0, -1},
            {-1, 2, 0}
    };
    johnson(adj, dist);
    assert(dist_ok == dist);

    std::cout << "Johnson test: OK" << std::endl;
}

void test_tree_hashing() {
    std::vector<char> treeA = {'(', '(', ')', '(', '(', ')', '(', ')', ')', ')'};
    std::vector<char> treeB = {'(', '(', '(', ')', '(', '(', ')', ')', ')', ')'};
    std::vector<char> treeC = {'(', '(', '(', ')', '(', ')', ')', '(', ')', ')'};

    auto hashA = hash_tree(treeA), hashB = hash_tree(treeB), hashC = hash_tree(treeC);
    assert(hashA != hashB);
    assert(hashA == hashC);
    std::cout << "Tree hashing test: OK" << std::endl;
}

void test_scc() {
    std::vector<std::vector<int>> adj0 = {
            {1},
            {2, 4},
            {0, 3},
            {},
            {3}
    };
    std::vector<int> components0 = {0, 0, 0, 2, 1};
    assert(components0 == get_scc(5, adj0));

    std::vector<std::vector<int>> adj1 = {
            {1},
            {2},
            {0, 3},
            {1}
    };
    std::vector<int> components1 = {0, 0, 0, 0};
    assert(components1 == get_scc(4, adj1));

    std::cout << "Strongly connected components test: OK" << std::endl;
}

void test_topological_sort() {
     std::vector<std::vector<int>> adj0 = {
         {2, 4, 5},
         {4, 5},
         {3, 4},
         {},
         {5},
         {}
     };
    std::vector<std::vector<int>> sorted0;
    std::vector<std::vector<int>> sorted_correct0 = {
            {0, 1},
            {2},
            {3, 4},
            {5}
    };
    assert(toposort(sorted0, adj0) == true);
    assert(sorted_correct0 == sorted0);
    std::vector<std::vector<int>> adj1 = {
            {1},
            {2},
            {0}
    };
    std::vector<std::vector<int>> sorted1;
    assert(toposort(sorted1, adj1) == false);
    std::cout << "Topological sort test: OK" << std::endl;
}

int main() {
    test_dwyer();
    test_edmonds_karp();
    test_floyd_warshall();
    test_bipartite();
    test_turbo_matching();
    test_bellman_ford();
    test_dijkstra();
    test_johnson();
    test_tree_hashing();
    test_scc();
    test_topological_sort();
    return 0;
}