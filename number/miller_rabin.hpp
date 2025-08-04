/**
 * An implementation of the Miller-Rabin primality test in C++.
 * This algorithm tests the primality of natural number up to 10^18.
 * It uses randomization for the choice of bases and fast modular exponentiation.
 * Created on 15.05.2024
 */

#include <vector>
#define u128 __uint128_t

#ifndef ALGORITHMS_MILLER_RABIN_H
#define ALGORITHMS_MILLER_RABIN_H

u128 power(u128, u128, u128);

/**
 * Perform Miller-Rabin primality test
 * @param n      number to be tested for primality
 * @return       true if prime else false
 */
bool miller_rabin(u128 n) {
    u128 s = __builtin_ctz(n-1), d = (n - 1) >> s;
    std::vector<u128> primes = {2, 3, 5, 7, 9, 11, 13, 17, 19, 23};
    for (auto a : primes) {
        if (a >= n) {
            return true;
        }
        u128 r = power(a, d, n);
        if (r == 1 || r == n - 1) {
            continue;
        }
        bool composite = true;
        for (int i = 0; i < s; i++) {
            r *= r;
            r %= n;
            if (r == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) {
            return false;
        }
    }
    return true;
}

/**
 * Calculate (a^d mod n) using fast exponentiation
 * @param a      base
 * @param d      exponent
 * @param n      modulo base
 * @return       Result of exponentiation
 */
u128 power(u128 a, u128 d, u128 n) {
    u128 res = 1;
    while (d > 0) {
        if (d & 1) {
            res = (res * a) % n;
        }
        a = (a * a) % n;
        d >>= 1;
    }
    return res;
}

#endif //ALGORITHMS_MILLER_RABIN_H