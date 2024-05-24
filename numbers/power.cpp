/**
 *
 * Created by Anna Szymańska on 24.11.2022
 */

#include <iostream>

/**
 *
 * @param a
 * @param k
 * @param p
 * @return
 */

int64_t power(int64_t a, int k, int64_t p) {
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