/**
 * Algorithm to solve the system of n equations
 * of the form Ax = b for m values of b using
 * the LU decomposition with partial pivoting.
 * Time complexity: O(n^2 * m)
 * Space complexity: O(n^2)
 * Created on 24.02.2025
 */

#include <vector>
#include <algorithm>
#include "decompositions.hpp"

#ifndef ALGORITHMS_SYSTEM_SOLVER_H
#define ALGORITHMS_SYSTEM_SOLVER_H

/**
 * Perform pivoting
 * @param n     number of equations
 * @param A     coefficients matrix
 * @param pi    permutation vector
 */
void pivot(int n, std::vector<std::vector<double>> & A, std::vector<int> & pi) {
    for (int i = 0; i < n; i++) {
        pi[i] = i;
    }
    for (int i = 0; i < n; i++) {
        auto it = std::max_element(A.begin()+i, A.end(), [&](std::vector<double> a, std::vector<double> b)
        {
            return std::abs(a[i]) < std::abs(b[i]);
        });
        int pivot_idx = it - A.begin();
        if (pivot_idx != i) {
            std::swap(A[i], A[pivot_idx]);
            std::swap(pi[i], pi[pivot_idx]);
        }
    }
}

/**
 * Solve the equations
 * @param n     number of equations
 * @param m     number of systems (different values of b)
 * @param A     coefficient matrix
 * @param B     free variables matrix
 */
std::vector<std::vector<double>> multi_solve(int n, std::vector<std::vector<double>> & A, const std::vector<std::vector<double>> & B) {
    std::vector<int> pi(n);
    pivot(n, A, pi);

    std::vector<std::vector<double>> L(n, std::vector<double>(n, 0)), U(n, std::vector<double>(n, 0));
    decompose_lu(n, A, L, U);

    std::vector<std::vector<double>> X;
    for (auto b : B) {
        std::vector<double> x(n);

        std::vector<double> b_pivoted(n);
        for (int i = 0; i < n; i++) {
            b_pivoted[i] = b[pi[i]];
        }

        /* LY=b */
        std::vector<double> y(n);
        y[0] = b_pivoted[0];
        for (int i = 1; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += y[j] * L[i][j];
            }
            y[i] = b_pivoted[i] - sum;
        }
        /* UX=Y */
        x[n-1] = y[n-1] / U[n-1][n-1];
        for (int i = n-2; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i+1; j < n; j++) {
                sum += U[i][j] * x[j];
            }
            x[i] = (y[i] - sum) / U[i][i];
        }
        X.push_back(x);
    }
    return X;
}

#endif //ALGORITHMS_SYSTEM_SOLVER_H