/**
 * The modified Gram-Schmidt algorithm to find orthonormal vectors
 * with the same span as input vectors, i.e. orthonormalize
 * the input matrix. The modified version ensures better numerical stability.
 * Time complexity: O(N * D^2), for N vectors from R^D
 * Space complexity: O(D^2)
 * Created on 25.02.2025
 */

#include <numeric>
#include <cmath>
#include <vector>

/**
 * Perform modified Gram-Schmidt orthogonalization
 * @param A     input matrix of N vectors from R^D
 * @param Q     output matrix of orthonormal vectors
 */
void gram_schmidt(const std::vector<std::vector<double>> & A, std::vector<std::vector<double>> & Q) {
    std::vector<std::vector<double>> V = A;
    int N = static_cast<int>(A.size()), D = static_cast<int>(A[0].size());
    Q.resize(N, std::vector<double>(D));
    for (int i = 0; i < N; i++) {
        auto vi = V[i];
        auto v_norm = sqrt(std::inner_product(vi.begin(), vi.end(), vi.begin(), 0.0));
        for (int j = 0; j < D; j++) {
            Q[i][j] = vi[j] / v_norm;
        }
        for (int k = i+1; k < N; k++) {
            auto qi = Q[i];
            auto & vk = V[k];
            auto qi_vk = std::inner_product(qi.begin(), qi.end(), vk.begin(), 0.0);
            for (int j = 0; j < D; j++) {
                V[k][j] -= qi[j] * qi_vk;
            }
        }
    }
}
