/**
 * Implementation of the Tonelli-Shanks algorithm
 * for computing discrete square root in modular arithmetic.
 * Time complexity: O(log n) randomized
 * Space complexity: O(1)
 * Created on 17.04.2025
 */

#include "../numbers/power.hpp"

#ifndef ALGORITHMS_TONELLI_SHANKS_HPP
#define ALGORITHMS_TONELLI_SHANKS_HPP

/** Solve y^2 = x (mod p) for y
 * @param x     integer such that 0 <= x < p
 * @param p     prime for modular operations
 * @return      y
 */
int tonelli_shanks(int x, int p) {
    if (p == 2) {
        return 1;
    }
    if (power(x, (p-1) / 2, p) != 1) {
        return 0;
    }
    int n = p-1, q = n / 2, t = n;
    int z = 2;
    srand(time(nullptr));
    while (power(z, n / 2, p) == 1) {
        z = rand() % (p-2) + 2;
    }
    while (q != 0 && q % 2 == 0) {
        q >>= 1;
        t >>= 1;
        if (power(x, q, p) * power(z, t, p) % p != 1) {
            t += n / 2;
        }
    }
    int64_t sqrt_x = power(x, (q+1) / 2, p) * power(z, t / 2, p);
    return (int)(sqrt_x % p);
}

#endif //ALGORITHMS_TONELLI_SHANKS_HPP
