#include "galois_field.hpp"

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

int main() {
    test_galois_field();
    return 0;
}