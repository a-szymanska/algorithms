/**
 * Compute prefix sum array.
 */

__global__ void kernel1(int n, int n_blocks, int64_t *A, int64_t *tmp_sum) {
    int id = threadIdx.x;
    int block_id = blockIdx.x;
    int global_id = block_id * 1024 + id;

    __shared__ int64_t tmp[1024];
    if (global_id < n) {
        tmp[id] = A[global_id];
    } else {
        tmp[id] = 0;
        return;
    }
    __syncthreads();

    for (int d = 1; id >= d && d < 1024; d *= 2) {
        int64_t x = tmp[id - d];
        __syncthreads();
        tmp[id] += x;
        __syncthreads();
    }

    A[global_id] = tmp[id];
    bool last = (block_id < n_blocks - 1 && id == 1023) || (block_id == n_blocks - 1 && global_id == n-1);
    if (last) {
        tmp_sum[block_id] = tmp[id];
    }
}

__global__ void kernel2(int64_t *tmp_sum, int n_blocks) {
    int id = threadIdx.x;
    if (id > 0) {
        return;
    }

    for (int i = 1; i < n_blocks; i++) {
        tmp_sum[i] += tmp_sum[i-1];
    }
}

__global__ void kernel3(int n, int64_t *A, int64_t *tmp_sum) {
    int block_id = blockIdx.x;
    int global_id = block_id * 1024 + threadIdx.x;

    if (block_id > 0 && global_id < n) {
        A[global_id] += tmp_sum[block_id - 1];
    }
}

void prefixsum(int n, int64_t *A, int64_t *S) {
    int n_blocks = (n + 1023) / 1024;

    int64_t *tmp_sum;
    cudaMalloc(&tmp_sum, n_blocks * sizeof(int64_t));

    kernel1<<<n_blocks, 1024>>>(n, n_blocks, A, tmp_sum);
    cudaDeviceSynchronize();

    kernel2<<<1, 1>>>(tmp_sum, n_blocks);
    cudaDeviceSynchronize();

    kernel3<<<n_blocks, 1024>>>(n, A, tmp_sum);
    cudaDeviceSynchronize();

    cudaMemcpy(S, A, n * sizeof(int64_t), cudaMemcpyDeviceToDevice);
    cudaFree(tmp_sum);
}