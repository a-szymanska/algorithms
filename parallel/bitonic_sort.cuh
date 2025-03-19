/**
 * Implementation of bitonic sort.
 * The code uses thrust library.
 */

#include <thrust/device_vector.h>
#include <thrust/copy.h>

#define MAX_VAL 1000000100

__device__ void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

__global__ void bitonic_kernel(int* a, int d, int w) {
    int id = threadIdx.x + blockDim.x * blockIdx.x;
    int k = id ^ d;

    if (k <= id) {
        return;
    }
    if (!(id & w) && (a[id] > a[k])) {
        swap(a + id, a + k);
    } else if ((id & w) && (a[id] < a[k])) {
        swap(a + id, a + k);
    }
}

void gpusort(int n, int* a) {
    int N = (1 << (std::__lg(n) + 1));
    int* a_adj;
    cudaMalloc(&a_adj, N * sizeof(int));
    cudaMemcpy(a_adj, a, n * sizeof(int), cudaMemcpyDeviceToDevice);
    cudaMemset(a_adj + n, MAX_VAL, (N - n) * sizeof(int));

    int n_threads = 256;
    int n_blocks = (N + n_threads - 1) / n_threads;
    for (int w = 2; w <= N; w *= 2) {
        for (int d = w >> 1; d > 0; d /= 2) {
            bitonic_kernel<<<n_blocks, n_threads>>>(a_adj, d, w);
        }
    }

    cudaMemcpy(a, a_adj, n * sizeof(int), cudaMemcpyDeviceToDevice);
    cudaFree(a_adj);
}
