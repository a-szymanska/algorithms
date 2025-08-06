/**
 * An implementation of the greatest common divisor finding algorithm in C++.
 * The algorithm supports natural number. It is provided in two variants:
 * the standard one (euclidean) and the one based on Stein's algorithm
 * that is without division or modulo operations which are typically significantly
 * slower than the logic operations.
 * Time complexity: O(log x * M(x)), where M(x) is complexity of multiplication of x, y
 * Space complexity: O(1)
 */

#ifndef ALGORITHMS_GCD_H
#define ALGORITHMS_GCD_H

#include <cstdint>

/**
 * Find GCD using the extended euclidean algorithm.
 * @param x, y  arguments
 * @param s, t  coefficients such that GCD(x, y) = xs + yt
 * @return      GCD(x, y)
 */
int64_t gcd(int64_t x, int64_t y, int64_t &s, int64_t &t) {
    if (y == 0) {
        s = 1;
        t = 0;
        return x;
    }
    int64_t s1, t1;
    int64_t d = gcd(y, x % y, s1, t1);
    s = t1;
    t = s1 - (x / y) * t1;
    return d;
}

/**
 * Find GCD using Stein's algorithm.
 * @param x         first number
 * @param y         second number
 * @return          gcd(x, y)
 */
int64_t gcd_stein(int64_t x, int64_t y) {
    int64_t shift_counter = 0;
    while (y > 0 && x > 0) {
        if (1 - (x & 1) && 1 - (y & 1)) {
            x = x >> 1;
            y = y >> 1;
            shift_counter++;
        } else if (1 - (x & 1)) {
            x = x >> 1;
        } else if (1 - (y & 1)) {
            y = y >> 1;
        } else if (x >= y) {
            x = (x - y) >> 1;
        } else {
            int64_t z = x;
            x = y;
            y = z;
            x = (x - y) >> 1;
        }
    }
    return y << shift_counter;
}

#endif //ALGORITHMS_GCD_H