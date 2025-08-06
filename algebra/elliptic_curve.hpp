/*
 * Implementation of the elliptic curve structure.
 * If mod = 0: operate normally (for double, mpq_class, etc.).
 * If mod != 0: apply all operations modulo mod (only valid for integer types like int, std::int64_t std::int64_t).
 */

#include <iostream>
#include <type_traits>
#include "../number/gcd.hpp"

#ifndef ALGORITHMS_ELLIPTIC_CURVE_HPP
#define ALGORITHMS_ELLIPTIC_CURVE_HPP

std::int64_t inv(std::int64_t x, std::int64_t mod) {
    std::int64_t s, t;
    gcd(x, mod, s, t);
    return s;
}

template<typename T>
struct Point {
    T x, y;
    bool is_O = false;

    Point() : x(0), y(0), is_O(true) {}
    Point(T x, T y) : x(x), y(y), is_O(false) {}

    friend std::ostream& operator<<(std::ostream& out, const Point<T>& p) {
        if (p.is_O) return out << "O";
        return out << "(" << p.x << ", " << p.y << ")";
    }
};

// y^2 = x^3 + Ax^2 + Bx
template<typename T, int mod>
struct EllipticCurve {
    T A, B;

    EllipticCurve(T A, T B) : A(A), B(B) {}

    Point<T> add(const Point<T>& P, const Point<T>& Q) const {
        if (P.is_O) return Q;
        if (Q.is_O) return P;

        if ((P.x == Q.x) && ((P.y + Q.y) % mod == 0)) {
            return Point<T>();
        }

        T lambda;
        if (P.x == Q.x) {
            T num = (3 * P.x * P.x + 2 * A * P.x + B) % mod;
            T den = (2 * P.y) % mod;
            lambda = (num * inv(den, mod)) % mod;
        } else {
            T num = (Q.y - P.y) % mod;
            T den = (Q.x - P.x) % mod;
            lambda = (num * inv(den, mod)) % mod;
        }

        T xr = (lambda * lambda - P.x - Q.x + mod) % mod;
        T yr = (-P.y - lambda * (xr - P.x) + mod) % mod;
        return Point<T>(xr, yr);
    }
};

template<typename T>
struct EllipticCurve<T, 0> {
    T A, B;

    EllipticCurve(T A, T B) : A(A), B(B) {}

    Point<T> add(const Point<T>& P, const Point<T>& Q) const {
        if (P.is_O) return Q;
        if (Q.is_O) return P;

        if (P.x == Q.x && P.y + Q.y == T(0)) {
            return Point<T>();
        }

        T lambda;
        if (P.x == Q.x) {
            lambda = (3 * P.x * P.x + 2 * A * P.x + B) / (2 * P.y);
        } else {
            lambda = (Q.y - P.y) / (Q.x - P.x);
        }

        T xr = lambda * lambda - P.x - Q.x;
        T yr = -P.y - lambda * (xr - P.x);
        return Point<T>(xr, yr);
    }
};

#endif // ALGORITHMS_ELLIPTIC_CURVE_HPP
