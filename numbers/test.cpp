#include "miller_rabin.cpp"
#include "gcd.cpp"
#include "power.cpp"
#include "equation_solver.cpp"

#include <iostream>
#include <cassert>

void test_miller_rabin() {
    std::vector<uint64_t> prime_numbers = { 2, 3, 11, 263, 1223, 65537, 1225849, 122300003699 };
    std::vector<uint64_t> composite_numbers = { 4, 27, 87, 1001, 665280, 720720, 1441440, 122300000353 };
    std::vector<uint64_t> carmichael_numbers = { 561, 1105, 1729, 2465, 2821, 6601 };
    for (auto x : prime_numbers) {
        assert(miller_rabin(x) == true);
    }
    for (auto x : composite_numbers) {
        assert(miller_rabin(x) == false);
    }
    for (auto x : carmichael_numbers) {
        assert(miller_rabin(x) == false);
    }
    std::cout << "Miller-Rabin's test: OK" << std::endl;
}

void test_gcd() {
    assert(gcd(0, 117) == 117);
    assert(gcd(1024, 8) == 8);
    assert(gcd(120, 285) == 15);
    assert(gcd(65537, 42) == 1);
    std::cout << "GCD test: OK" << std::endl;
}

void test_gcd_stein() {
    assert(gcd_stein(0, 117) == 117);
    assert(gcd_stein(1024, 8) == 8);
    assert(gcd_stein(120, 285) == 15);
    assert(gcd_stein(65537, 42) == 1);
    std::cout << "Stein's GCD test: OK" << std::endl;
}

void test_power() {
    std::cout << "Power test: OK" << std::endl;
}

void test_equation_solver() {
    std::cout << "Equation solver test: OK" << std::endl;
}

int main() {
    test_miller_rabin();
    test_gcd();
    test_gcd_stein();
    return 0;
}