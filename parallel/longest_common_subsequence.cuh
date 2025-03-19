/**
 * Given two strings, find their longest common subsequence.
 * The code uses Moderngpu library: https://github.com/moderngpu/moderngpu.
 */


#include <vector>
#include <string>
#include <algorithm>
#include <cuda_runtime.h>
#include "moderngpu/transform.hxx"
#include "moderngpu/memory.hxx"


/**
 * @param X, Y      input strings, assumption: |X| >= |Y|
 * @param m         length of X
 * @param n         length of Y
 * @return          length of LCS(X, Y)
 */
int get_lcs_cuda(const std::string& X, const std::string& Y, int m, int n) {
    mgpu::standard_context_t context(false);
    mgpu::mem_t<int> d_diag[3] = {
            mgpu::fill<int>(0, n + 1, context),
            mgpu::fill<int>(0, n + 1, context),
            mgpu::fill<int>(0, n + 1, context),
    };

    std::vector<char> vec_X(X.begin(), X.end());
    std::vector<char> vec_Y(Y.begin(), Y.end());
    mgpu::mem_t<char> d_X = mgpu::to_mem(vec_X, context);
    mgpu::mem_t<char> d_Y = mgpu::to_mem(vec_Y, context);

    int idx = 0;
    for (int d = 0; d <= m + n; d++, idx = (++idx) % 3) {
        auto f = [=]MGPU_DEVICE(int k, int* prev_prev_diag, int* prev_diag, int* curr_diag, const char* X, const char* Y) {
            int i = k + max(1, d - n);
            int j = d - i;

            if (i <= 0 || i > m || j <= 0 || j > n) {
                return;
            }
            if (X[i - 1] == Y[j - 1]) {
                curr_diag[j] = prev_prev_diag[j - 1] + 1;
            } else {
                curr_diag[j] = max(prev_diag[j], prev_diag[j - 1]);
            }
        };

        mgpu::transform(f, n + 1, context,
                        d_diag[idx % 3].data(), d_diag[(idx + 1) % 3].data(), d_diag[(idx + 2) % 3].data(),
                        d_X.data(), d_Y.data()
        );
    }

    std::vector<int> h_lcs = mgpu::from_mem(d_diag[(idx + 1) % 3]);
    return h_lcs[n];
}