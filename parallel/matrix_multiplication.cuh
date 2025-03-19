/**
 * Multiply square matrices.
 */

#include <cuda.h>

__global__ void matrixMultiplyKernel(int n, float *A, float *B, float *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        float sum = 0.0;
        for (int k = 0; k < n; ++k) {
            sum += A[row * n + k] * B[k * n + col];
        }
        C[row * n + col] = sum;
    }
}

void matmul(int n, float *A, float *B, float *C) {
    dim3 n_threads(16, 16);
    dim3 n_blocks((n + n_threads.x - 1) / n_threads.x,
                  (n + n_threads.y - 1) / n_threads.y);

    matrixMultiplyKernel<<<n_blocks, n_threads>>>(n, A, B, C);
    cudaDeviceSynchronize();
}