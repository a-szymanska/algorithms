/**
 * Algorithm to find the smallest x satisfying the equation
 * a^x = b mod p.
 * Time complexity: O(sqrt(p)*lg(p))
 * Space complexity: O(sqrt(p))
 * Created on 24.04.2024
 */

#include <iostream>
#include <vector>
#include <unordered_map>

/**
 * Solve the equation
 * @param a     first constant
 * @param b     second constant
 * @param p     modular base
 * @return
 */
int64_t solve(int64_t a, int64_t b, int64_t p) {
    if (a*b == 0 && a+b == 0) {
        return 1 - 2 * (a + b != 0);
    }
    int64_t w = 1;
    while (w*w < p) {
        w++;
    }
    std::vector<int> rests(p, -1);
    for (int j = 0; j < w; j++) {
        auto r = power(a, p-j-1, p);
        auto br = (b*r) % p;
        if (rests[br] == -1) {
            rests[br] = j;
        }
    }
    auto a_w = power(a, w, p);
    for (int i = 0, r = 1; i < w; i++) {
        if (rests[r] != -1) {
            auto j = rests[r];
            return (i*w+j) % p;
        }
        r = (r * a_w) % p;
    }
    return -1;
}