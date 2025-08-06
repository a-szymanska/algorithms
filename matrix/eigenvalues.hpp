/**
 * Implementation of the QR method for finding eigenvalues
 * of a symmetric matrix. May give incorrect results for
 * matrix with no dominant eigenvalue.
 * Time complexity: O(N * D^2), for N vectors from R^D
 * Space complexity: O(D^2)
 */

#include <vector>
#include <numeric>
#include <cmath>
#include "decompositions.hpp"

#ifndef ALGORITHMS_EIGENVALUES_H
#define ALGORITHMS_EIGENVALUES_H

#define EPS 0.000001

/**
 * Compute approximate eigenvalues of A
 * @param n     size of A
 * @param A     symmetric matrix
 */
std::vector<double> get_spectrum(int n, std::vector<std::vector<double>> & A) {
    if (n == 1) {
        return {A[0][0]};
    }

    std::vector<double> prev(n);
    for (int i = 0; i < n; i++) {
        prev[i] = A[i][i];
    }
    bool changing = true;
    while (changing) {
        std::vector<std::vector<double>> Q(n, std::vector<double>(n, 0)), R(n, std::vector<double>(n, 0));
        int l = A[n-1][n-1];
        for (int i = 0; i < n; i++) {
            A[i][i] -= l;
        }
        decompose_qr(n, n, A, Q, R);
        for (int i = 0; i < n; i++) {
            std::fill(A[i].begin(), A[i].end(), 0.0);
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    A[i][j] += R[i][k] * Q[k][j];
                }
            }
            A[i][i] += l;
        }
        changing = false;
        for (int i = 0; i < n; i++) {
            changing |= (std::abs(prev[i] - A[i][i]) > EPS);
            prev[i] = A[i][i];
        }
    }

    std::vector<double> eigenvalues(n);
    for (int i = 0; i < n; i++) {
        if (A[i][i] != A[i][i]) {
            eigenvalues[i] = 0;
        } else {
            eigenvalues[i] = A[i][i];
        }
    }
    return eigenvalues;
}

#endif //ALGORITHMS_EIGENVALUES_H