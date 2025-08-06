#include "elliptic_curve.hpp"
#include <iostream>

int main() {
    // y^2 = x^3 + 2x^2 + 3x, mod = 17
    EllipticCurve<std::int64_t, 17> curve0(2, 3);
    Point<std::int64_t> P0(5, 1);
    Point<std::int64_t> Q0(6, 3);

    Point<std::int64_t> R0 = curve0.add(P0, Q0);
    std::cout << "P + Q = " << R0 << '\n';

    // y^2 = x^3 + 2x^2 + 3x
    EllipticCurve<double, 0> curve1(2.0, 3.0);
    Point<double> P1(5.0, 1.0);
    Point<double> Q1(6.0, 3.0);

    Point<double> R1 = curve1.add(P1, Q1);
    std::cout << "P + Q = " << R1 << '\n';

    return 0;
}
