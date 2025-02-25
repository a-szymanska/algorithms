#include "system_solver.hpp"
#include "gram_schmidt.hpp"
#include "eigenvalues.hpp"

#include <iostream>
#include <cassert>
#include <numeric>


void test_systems() {
    int n = 3, m = 2;
    std::vector<std::vector<double>> A = {
            {-1, 3, 1},
            {0, 1, 1},
            {2, 1, -1}
    };
    std::vector<std::vector<double>> B = {
            {-5, 2, 0},
            {3, -7, 6}
    };
    std::vector<std::vector<double>> solutions = {
            {3, -2, 4},
            {-3.66667, 3.16667, -10.1667}
    };
    auto X = multi_solve(n, A, B);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            assert(std::abs(solutions[i][j] - X[i][j]) < 0.0001);
        }
    }
    std::cout << "Solving systems of equations test: OK" << std::endl;
}

void test_orthogonalization() {
    int n = 2;
    std::vector<std::vector<double>> A = {
            {6, 8, 0},
            {10, 5, 12}
    };
    std::vector<std::vector<double>> Q;
    gram_schmidt(A, Q);
    for (int i = 0; i < n; i++) {
        auto norm_i = std::inner_product(Q[i].begin(), Q[i].end(), Q[i].begin(), 0.0);
        assert(std::abs(norm_i - 1) < 0.0001);
        for (int j = i + 1; j < n; j++) {
            auto prod_ij = std::inner_product(Q[i].begin(), Q[i].end(), Q[j].begin(), 0.0);
            assert(std::abs(prod_ij) < 0.0001);
        }
    }
    std::cout << "Orthogonalization test: OK" << std::endl;
}

void test_eigenvalues() {
    int n = 3;
    std::vector<std::vector<double>> A = {
             {1, 4, 0},
             {4, -2, 7.5},
             {0, 7.5, 5}
    };
    auto solutions = std::vector<double>({-8.06856, 1.75799, 10.3106});
    auto eigenvalues = get_spectrum(3, A);
    std::sort(eigenvalues.begin(), eigenvalues.end());
    for (int i = 0; i < n; i++) {
        assert(std::abs(solutions[i] - eigenvalues[i]) < 0.0001);
    }
    std::cout << "Eigenvalues test: OK" << std::endl;
}


int main() {
    test_systems();
    test_orthogonalization();
    test_eigenvalues();
    return 0;
}