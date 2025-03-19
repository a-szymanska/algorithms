/**
 * Given an undirected graph, find its decomposition into connected components.
 * The code uses thrust library.
 */

#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/copy.h>
#include <thrust/sequence.h>
#include <algorithm>

__global__ void edge_doubler_kernel(int m, int* d_edges);

__global__ void dir_counter_kernel(int m, int* incr, int* decr, int* d_edges);

__global__ void edge_maker_kernel(int m, int *S, int* d_cc, int *d_edges);

__global__ void edge_director_kernel(int m, bool moreInc, int* d_cc, int *d_edges);

__global__ void edge_updater_kernel(int m, int *S, int *d_cc, int *d_edges);

__global__ void pointer_jumper_kernel(int n, int *d_cc, int *d_working);


/**
 * Assign each vertex number c of its connected component 0 <= c <= n-1.
 * @param n         number of vertices (vertices are indexed from 0)
 * @param m         number of edges
 * @param edges     array of length 2m,
 *                  numbers (2i)-th and (2i+1)-th give ends of edge
 * @param cc        output array of length n,
 *                  cc[i] is number of component containing vertex i
 */
void find_cc(int n, int m, int* edges, int* cc) {
    // Params for kernels
    int block = 512;
    int n_blocks_n = (n + block - 1) / block;
    int n_blocks_m = (m + block - 1) / block;
    int n_blocks_2m = (2 * m + block - 1) / block;

    thrust::device_vector<int> d_edges(edges, edges + 2 * m);
    thrust::device_vector<int> d_cc(cc, cc + n);
    d_edges.resize(4 * m);
    edge_doubler_kernel<<<n_blocks_m, block>>>(m, thrust::raw_pointer_cast(d_edges.data()));
    thrust::sequence(d_cc.begin(), d_cc.end());

    while (m > 0) {
        thrust::device_vector<int> incr(n, 0), decr(n, 0), S(2 * m);
        dir_counter_kernel<<<n_blocks_m, block>>>(
                m, thrust::raw_pointer_cast(incr.data()), thrust::raw_pointer_cast(decr.data()), thrust::raw_pointer_cast(d_edges.data())
        );

        int inc = thrust::reduce(incr.begin(), incr.end(), 0, thrust::plus<int>());
        int dec = thrust::reduce(decr.begin(), decr.end(), 0, thrust::plus<int>());
        edge_director_kernel<<<n_blocks_2m, block>>>(
                m, (inc >= dec), thrust::raw_pointer_cast(d_cc.data()), thrust::raw_pointer_cast(d_edges.data())
        );
        int changing;
        do {
            thrust::device_vector<int> d_working(1);
            pointer_jumper_kernel<<<n_blocks_n, block>>>(
                    n, thrust::raw_pointer_cast(d_cc.data()), thrust::raw_pointer_cast(d_working.data())
            );
            thrust::copy(d_working.begin(), d_working.end(), &changing);
        } while (changing);

        edge_maker_kernel<<<n_blocks_2m, block>>>(
                m, thrust::raw_pointer_cast(S.data()), thrust::raw_pointer_cast(d_cc.data()), thrust::raw_pointer_cast(d_edges.data())
        );
        thrust::inclusive_scan(S.begin(), S.begin() + 2 * m, S.begin());

        int mm = S[2 * m - 1] / 2;
        edge_updater_kernel<<<n_blocks_2m, block>>>(
                m, thrust::raw_pointer_cast(S.data()), thrust::raw_pointer_cast(d_cc.data()), thrust::raw_pointer_cast(d_edges.data())
        );
        m = mm;
    }

    thrust::copy(d_cc.begin(), d_cc.end(), cc);
}

__global__ void edge_doubler_kernel(int m, int* d_edges) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < m) {
        d_edges[2 * m + 2 * i] = d_edges[2 * i + 1];
        d_edges[2 * m + 2 * i + 1] = d_edges[2 * i];
    }
}

__global__ void dir_counter_kernel(int m, int* incr, int* decr, int* d_edges) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < m) {
        int u = d_edges[2 * i], v = d_edges[2 * i + 1];
        if (u < v) {
            incr[u] = 1;
        } else {
            decr[u] = 1;
        }
    }
}

__global__ void edge_maker_kernel(int m, int *S, int* d_cc, int *d_edges) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < 2 * m) {
        int u = d_edges[2 * i], v = d_edges[2 * i + 1];
        S[i] = (d_cc[u] != d_cc[v]) ? 1 : 0;
    }
}

__global__ void edge_director_kernel(int m, bool moreInc, int* d_cc, int *d_edges) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < 2 * m) {
        int u = d_edges[2 * i], v = d_edges[2 * i + 1];
        if (moreInc && u < v) {
            d_cc[u] = v;
        } else if (!moreInc && u > v) {
            d_cc[u] = v;
        }
    }
}

__global__ void edge_updater_kernel(int m, int *S, int *d_cc, int *d_edges) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < 2 * m) {
        int u = d_edges[2 * i], v = d_edges[2 * i + 1];
        if (d_cc[u] != d_cc[v]) {
            d_edges[2 * S[i] - 2] = d_cc[u];
            d_edges[2 * S[i] - 1] = d_cc[v];
        }
    }
}

__global__ void pointer_jumper_kernel(int n, int *d_cc, int *d_working) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        int n_iter = 24, prev_cc = -1;
        while (n_iter--) {
            prev_cc = d_cc[i];
            d_cc[i] = d_cc[d_cc[i]];
        }
        if (prev_cc != d_cc[i]) {
            d_working[0] = 1;
        }
    }
}