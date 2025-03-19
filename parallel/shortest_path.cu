/**
 * Given an undirected graph in SNAP format (https://snap.stanford.edu/data),
 * for each vertex find the maximal length of the shortest path from this vertex
 * to any vertex in the graph.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "moderngpu/memory.hxx"
#include "moderngpu/transform.hxx"
#include <cuda_runtime.h>

__global__ void bfs_iteration(int n, int iter_cnt, int* iter, int* adj, std::pair<int, int>* adj_idx, bool* done) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id >= n) {
        return;
    }

    if (iter[id] == iter_cnt) {
        for (int i = adj_idx[id].first; i < adj_idx[id].second; i++) {
            int y = adj[i];
            if (atomicCAS(&iter[y], -1, iter_cnt + 1) == -1) {
                *done = false;
            }
        }
    }
}

int part_diameter(int x, int n, int m, int* d_adj, std::pair<int, int>* d_adj_idx) {
    std::vector<int> iter(n, -1);
    iter[x] = 0;

    int* d_iter;
    bool* d_done;

    cudaMalloc(&d_iter, n * sizeof(int));
    cudaMalloc(&d_done, sizeof(bool));
    cudaMemcpy(d_iter, iter.data(), n * sizeof(int), cudaMemcpyHostToDevice);

    int iter_cnt = -1;
    bool done = false;
    int n_threads = 256;
    int n_blocks = (n + n_threads - 1) / n_threads;
    while (!done) {
        ++iter_cnt;
        done = true;
        cudaMemcpy(d_done, &done, sizeof(bool), cudaMemcpyHostToDevice);
        bfs_iteration<<<n_blocks, n_threads>>>(n, iter_cnt, d_iter, d_adj, d_adj_idx, d_done);
        cudaMemcpy(&done, d_done, sizeof(bool), cudaMemcpyDeviceToHost);
    }

    cudaFree(d_iter);
    cudaFree(d_done);

    return iter_cnt;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::pair<int, int>> edges;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        std::istringstream istr(line);
        int x, y;
        if (istr >> x >> y) {
            edges.emplace_back(x, y);
            edges.emplace_back(y, x);
        }
    }

    std::sort(edges.begin(), edges.end());
    int m = edges.size(), n = edges[m - 1].first + 1;
    std::vector<int> adj(m);
    std::vector<std::pair<int, int>> adj_idx(n);
    int x, y, x_prev = 0;
    adj_idx[0].first = 0;
    adj_idx[n - 1].second = m;
    for (int i = 0; i < m; i++) {
        x = edges[i].first, y = edges[i].second;
        adj[i] = y;
        if (x != x_prev) {
            adj_idx[x_prev].second = adj_idx[x].first = i;
            x_prev = x;
        }
    }

    int* d_adj;
    std::pair<int, int>* d_adj_idx;

    cudaMalloc(&d_adj, m * sizeof(int));
    cudaMalloc(&d_adj_idx, n * sizeof(std::pair<int, int>));
    cudaMemcpy(d_adj, adj.data(), m * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_adj_idx, adj_idx.data(), n * sizeof(std::pair<int, int>), cudaMemcpyHostToDevice);

    for (int i = 0; i < n; i++) {
        std::cout << part_diameter(i, n, m, d_adj, d_adj_idx) << "\n";
    }

    cudaFree(d_adj);
    cudaFree(d_adj_idx);
    return 0;
}
