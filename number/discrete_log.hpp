/**
 * Algorithm to find the smallest solution to discrete logarithm
 * using the Baby-Step-Giant-Step method.
 * Time complexity: O(sqrt(p)*lg(p))
 * Space complexity: O(sqrt(p))
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

#include "power.hpp"

#ifndef ALGORITHMS_EQUATION_SOLVER_HPP
#define ALGORITHMS_EQUATION_SOLVER_HPP

/**
 * Solve a^x = b (mod p) for x
 * @param a     first constant
 * @param b     second constant
 * @param p     modular base
 * @return
 */
int64_t solve(int64_t a, int64_t b, int64_t p) {
    if (a == 0 && b == 0) {
        return -1;
    }
    int64_t sqrt_p = std::ceil(std::sqrt(p));
    std::unordered_map<int64_t, int> map;
    for (int j = 0; j < sqrt_p; j++) {
        auto r = pow(a, p-j-1, p);
        auto br = (b*r) % p;
        if (map.find(br) == map.end()) {
            map[br] = j;
        }
    }
    int64_t a_pow = pow(a, sqrt_p, p);
    int64_t r = 1;
    for (int i = 0; i < sqrt_p; i++) {
        if (map.find(r) != map.end()) {
            auto j = map[r];
            return (i * sqrt_p + j) % p;
        }
        r = (r * a_pow) % p;
    }
    return -1;
}

#endif //ALGORITHMS_EQUATION_SOLVER_HPP