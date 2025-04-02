/**
 * The implementation of Galois field GF(256)
 * with arithmetic modulo (x^8 + x^4 + x^3 + x^2 + 1).
 * Created on 01.04.2024
 */

#include <iostream>
#include <vector>
#include <random>

#ifndef ALGORITHMS_GALOIS_FIELD_HPP
#define ALGORITHMS_GALOIS_FIELD_HPP


struct gf_256 {
    int32_t p;
    static constexpr int g = 0x11D;
    static constexpr int bit8 = 0x100;

    static std::mt19937 gen;
    static std::uniform_int_distribution<int> dist;

    gf_256() : p(0) {}
    gf_256(int32_t p) : p(p) {}

    gf_256 inv() {
        return gf_256(1) / *this;
    }

    static gf_256 random() {
        return gf_256(dist(gen));
    }

    friend gf_256 operator+(const gf_256& x, const gf_256& y) {
        return gf_256(x.p ^ y.p);
    }

    friend gf_256 operator*(const gf_256& x, const gf_256& y) {
        int32_t a = x.p, b = y.p;
        int32_t res = 0;
        while (b) {
            if (b & 1) {
                res ^= a;
            }
            b >>= 1;
            a <<= 1;
            if (a & bit8) {
                a ^= g;
            }
        }
        return gf_256(res);
    }

    friend gf_256 operator/(const gf_256& x, gf_256 y) {
        gf_256 res = 1;
        int pow = 254;
        while (pow) {
            if (pow & 1) {
                res = res * y;
            }
            y = y * y;
            pow >>= 1;
        }
        return x * res;
    }

    friend bool operator==(const gf_256& x, const gf_256& y) {
        return x.p == y.p;
    }

    friend bool operator<(const gf_256& x, const gf_256& y) {
        return x.p < y.p;
    }

    friend std::ostream& operator<<(std::ostream& out, const gf_256& x) {
        out << x.p;
        return out;
    }

};
std::mt19937 gf_256::gen(std::random_device{}());
std::uniform_int_distribution<int> gf_256::dist(0, 255);


#endif //ALGORITHMS_GALOIS_FIELD_HPP
