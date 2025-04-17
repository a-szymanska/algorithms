#include "finite_field.hpp"
#include "polynomial_primality.hpp"
#include "tonelli_shanks.hpp"

#include <iostream>
#include <cassert>


void test_galois_field() {
    gf_256 a(51), b(307), c(20);
    assert((a + b) == (b + a) && (a + b) == gf_256(256));
    assert((a + 0) == a);
    assert((a + a) == gf_256(0));

    assert((a * 1) == a);
    assert((a * 0) == gf_256(0));
    assert((a * (b + c)) == (a * b + a * c) && (a * (b + c)) == gf_256(218));

    assert((a / a) == gf_256(1));
    assert((a / 1) == a);
    assert((a / c) == gf_256(202));

    gf_256 inv_a = a.inv();
    assert((inv_a * a) == gf_256(1));

    std::cout << "Galois field test: OK" << std::endl;
}

void test_polynomial_primality() {
    poly_zp::p = 2;
    poly_zp X0({1, 0, 2, 1}); // x^3 + 2x^2 + 1 = (x + 1) * (x^2 + x + 1)
    poly_zp res0 = is_prime(X0, poly_zp::p);
    assert(res0.deg() > 0);

    poly_zp::p = 2;
    poly_zp X1({1, 1, 1}); // x^2 + x + 1
    poly_zp res1 = is_prime(X1, poly_zp::p);
    assert(res1.deg() == 0);

    std::cout << "Polynomial primality test: OK" << std::endl;
}

void test_tonelli_shanks() {
    int64_t sqrt_x;
    assert((sqrt_x = tonelli_shanks(2, 7)) && sqrt_x * sqrt_x % 7 == 2);
    assert((sqrt_x = tonelli_shanks(4, 17)) && sqrt_x * sqrt_x % 17 == 4);
    assert(!(sqrt_x = tonelli_shanks(3, 17)));
    std::cout << "Tonelli-Shanks test: OK" << std::endl;
}

int main() {
    test_galois_field();
    test_polynomial_primality();
    test_tonelli_shanks();
    return 0;
}