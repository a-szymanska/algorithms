/**
 * Implementation of modular exponentiation by squaring
 * Time complexity: O(k)
 * Space complexity: O(1)
 */

#include <iostream>

#ifndef ALGORITHMS_POWER_H
#define ALGORITHMS_POWER_H

/**
 * Calculate a^k mod p
 * @param a     base
 * @param k     exponent
 * @param p     modular base
 * @return
 */
int64_t pow(int64_t a, int64_t k, int64_t p) {
    int64_t res = 1;
    while (k > 0) {
        if (k & 1) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        k >>= 1;
    }
    return res;
}

#endif //ALGORITHMS_POWER_H