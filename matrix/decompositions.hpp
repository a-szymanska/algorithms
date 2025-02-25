/**
 * Implementations of LU and QR matrix decompositions.
 * Time complexity: O(n^3)
 * Space complexity: O(n^2)
 * Created on 25.02.2025
 */

#include <vector>
#include <numeric>
#include <cmath>

#ifndef ALGORITHMS_DECOMPOSITIONS_H
#define ALGORITHMS_DECOMPOSITIONS_H

/**
 * Decompose A into L * U
 * @param n     number of equations
 * @param A     coefficients matrix
 * @param L     lower triangular matrix
 * @param U     upper triangular matrix
 */
void decompose_lu(int n, const std::vector<std::vector<double>> & A, std::vector<std::vector<double>> & L, std::vector<std::vector<double>> & U) {
    U[0] = A[0];
    for (int i = 0; i < n; i++) {
        L[i][i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += L[i][k] * U[k][j];
            }
            L[i][j] = (A[i][j] - sum) / U[j][j];
        }
        for (int j = i; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }
    }
}

/**
 * Decompose A into Q * R
 * @param n, m  dimensions of A
 * @param A     input matrix
 * @param Q     result orthogonal matrix
 * @param R     result upper triangular matrix
 */
void decompose_qr(int n, int m, std::vector<std::vector<double>> &A, std::vector<std::vector<double>> & Q, std::vector<std::vector<double>> & R) {
    std::vector<double> col_A(n, 0), col_Q(n, 0);
    for (int i = 0; i < m; i++) {
        std::fill(R[i].begin(), R[i].begin() + i, 0.0);

        for (int j = 0; j < n; j++) {
            col_A[j] = A[j][i];
        }
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < n; k++) {
                col_Q[k] = Q[k][j];
            }
            double aq = std::inner_product(col_A.begin(), col_A.end(), col_Q.begin(), 0.0);
            double qq = std::inner_product(col_Q.begin(), col_Q.end(), col_Q.begin(), 0.0);
            double x = aq / qq;
            for (int k = 0; k < n; k++) {
                col_Q[k] *= x;
                col_A[k] -= col_Q[k];
            }
        }
        double norm_A = sqrt(std::inner_product(col_A.begin(), col_A.end(), col_A.begin(), 0.0));
        for (int j = 0; j < n; j++) {
            Q[j][i] = col_A[j] / norm_A;
            col_Q[j] = Q[j][i];
        }

        for (int j = i; j < m; j++) {
            double r = 0.0;
            for (int k = 0; k < n; k++) {
                r += col_Q[k] * A[k][j];
            }
            R[i][j] = r;
        }
    }
}

#endif //ALGORITHMS_DECOMPOSITIONS_H
