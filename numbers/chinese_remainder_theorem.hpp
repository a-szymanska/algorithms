/**
 * Solving the system of congruence equations using
 * Chinese Remainder Theorem
 * Time complexity: O(n * logM), where M maximum modulus value
 * Space complexity: O(1)
 * Created on 12.03.2025
 */

#include <vector>
#include <numeric>
#include "gcd.hpp"

#ifndef ALGORITHMS_REMAINDER_H
#define ALGORITHMS_REMAINDER_H

/**
 * Find modular inverse of a (mod m).
 */
int inv(int a, int m) {
    int x, y;
    int d = gcd(a, m, x, y);
    if (d != 1) {   // a, m are not coprime
        return -1;
    }
    return (x % m + m) % m;
}

/**
 * Solve the system of congruences.
 * @param A, B, M   coefficients of equations of form:
 *                  A[i] * x = B[i] (mod M[i])
 *                  where M[i], M[j] are coprime
 * @return          minimal solution or -1 if there's no solution
 */
int solve_crt(const std::vector<int>& A, const std::vector<int>& B, const std::vector<int>& M) {
    int n = static_cast<int>(A.size());
    int x = 0, m = 1;
    for (int i = 0; i < n; i++) {
        int s, t, d = gcd(A[i], M[i], s, t);
        if (B[i] % d != 0) {
            return -1;
        }
        int ai = A[i] / d, bi = B[i] / d, mi = M[i] / d;
        int ai_inv = inv(ai, mi);
        int ri = (bi * ai_inv) % mi;
        int x_tmp;
        if (i == 0) {
            x_tmp = ri;
        } else {
            int m_inv = inv(m, mi);
            x_tmp = x + ((ri - x) * m_inv % mi) * m;
        }
        m *= mi;
        x = (x_tmp % m + m) % m;
    }
    return x;
}

#endif //ALGORITHMS_REMAINDER_H
