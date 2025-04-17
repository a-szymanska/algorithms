/**
 * The implementation of some finite fields
 * needed for algebra algorithms.
 * Created on 01.04.2024
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#ifndef ALGORITHMS_FINITE_FIELD_HPP
#define ALGORITHMS_FINITE_FIELD_HPP

/**
 * Galois field GF(256) with arithmetic modulo (x^8 + x^4 + x^3 + x^2 + 1)
 */
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

/**
 * Polynomials over the Zp field
 */
struct poly_zp {
    static int p;
    std::vector<int64_t> X; // od najmniejszych

    poly_zp() = default;
    explicit poly_zp(const std::vector<int64_t>& X) : X(X) {
        for (auto &x : this->X) {
            x = x % p;
        }
    }

    int deg() const {
        return std::max(0, static_cast<int>(X.size()-1));
    }

    bool zero() const {
        return (X.size() == 1 && X[0] == 0);
    }

    friend poly_zp operator+(const poly_zp& a, const poly_zp& b) {
        int d_a = a.deg(), d_b = b.deg();
        std::vector<int64_t> X_res(std::max(d_a, d_b) + 1, 0);
        copy(a.X.begin(), a.X.end(), X_res.begin());
        for (int i = 0; i <= d_b; i++) {
            X_res[i] = (X_res[i] + b.X[i]) % p;
        }
        poly_zp res(X_res);
        res.remove_zeros();
        return res;
    }

    friend poly_zp operator-(const poly_zp &a, poly_zp b) {
        int d_a = a.deg(), d_b = b.deg();
        std::vector<int64_t> X_res(std::max(d_a, d_b) + 1, 0);
        copy(a.X.begin(), a.X.end(), X_res.begin());
        for (int i = 0; i <= d_b; i++) {
            X_res[i] = (X_res[i] - b.X[i] + p) % p;
        }
        poly_zp res(X_res);
        res.remove_zeros();
        return res;
    }

    friend poly_zp operator*(const poly_zp& a, const poly_zp& b) {
        int64_t d_a = a.deg(), d_b = b.deg();
        int64_t d = d_a + d_b;
        std::vector<__int128_t> res_X(d + 1, 0);
        for (int i = 0; i <= d_a; i++) {
            for (int j = 0; j <= d_b; j++) {
                res_X[i + j] = (res_X[i + j] + a.X[i] * b.X[j]);
            }
        }
        std::vector<int64_t> res_X64(d + 1, 0);
        for (int i = 0; i <= d; i++) {
            res_X64[i] = res_X[i] % p;
        }
        return poly_zp(res_X64);
    }

    friend poly_zp operator/(const poly_zp& a, const poly_zp& b) {
        if (a.zero()) {
            return a;
        }
        poly_zp div, mod;
        div_mod(a, b, div, mod);
        return div;
    }

    friend poly_zp operator%(const poly_zp& a, const poly_zp& b) {
        if (a.zero()) {
            return a;
        }
        poly_zp div, mod;
        div_mod(a, b, div, mod);
        return mod;
    }

    friend poly_zp gcd(poly_zp a, poly_zp b) {
        while (!b.zero()) {
            poly_zp r = a % b;
            a = std::move(b);
            b = std::move(r);
        }
        return a;
    }

    friend poly_zp pow(poly_zp a, int64_t k, const poly_zp& m) {
        if (a.zero()) {
            return a;
        }
        poly_zp res({1});
        while (k > 0) {
            if (k & 1) {
                res = (res * a) % m;
            }
            a = (a * a) % m;
            k >>= 1;
        }

        for (auto& x : res.X) {
            x = x % p;
        }
        res.remove_zeros();
        return res;
    }

    friend std::ostream& operator<< (std::ostream& out, const poly_zp &a) {
        for (auto x : a.X) {
            out << x << " ";
        }
        return out;
    }

private:
    int64_t inv(int64_t x) const {
        int64_t res = 1, k = p-2;
        while (k > 0) {
            if (k & 1) {
                res = (res * x) % p;
            }
            x = (x * x) % p;
            k >>= 1;
        }
        return res;
    }

    void remove_zeros() {
        auto it = std::find_if(X.rbegin(), X.rend(), [](auto val){ return val != 0; });
        if (it == X.rend()) {
            X.resize(1);
        } else {
            X.erase(it.base(), X.end());
        }
    };

    friend void div_mod(const poly_zp &a, const poly_zp &b, poly_zp &div, poly_zp &mod) {
        div.X = {0};
        if (b.zero()) {
            mod.X = {0};
        }
        mod = a;

        while ((mod.deg() > 0 || mod.X[0] != 0) && mod.deg() >= b.deg()) {
            int64_t d = mod.deg() - b.deg();
            std::vector<int64_t> v_tmp(d + 1, 0);
            v_tmp[d] = mod.X[mod.deg()] * b.inv(b.X[b.deg()]);
            poly_zp tmp(v_tmp);
            div = div + tmp;
            mod = mod - tmp * b;
        }
        for (auto& x : div.X) {
            x = x % p;
        }
        div.remove_zeros();
    }
};
int poly_zp::p;

#endif //ALGORITHMS_FINITE_FIELD_HPP
