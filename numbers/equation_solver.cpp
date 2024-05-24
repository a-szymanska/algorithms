/**
 *
 * Created by Anna Szymańska on 24.11.2022
 */

#include <iostream>
#include <vector>
#include <unordered_map>


/**
 *
 * @param a
 * @param b
 * @param p
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
    std::unordered_map<int64_t, int> map;
    for (int j = 0; j < w; j++) {
        auto r = power(a, p-j-1, p);
        auto br = (b*r) % p;
        if (map.find(br) == map.end()) {
            map[br] = j;
        }
    }
    auto a_w = power(a, w, p);
    for (int i = 0, r = 1; i < w; i++) {
        if (map.find(r) != map.end()) {
            auto j = map[r];
            return (i*w+j) % p;
        }
        r = (r * a_w) % p;
    }
    return -1;
}