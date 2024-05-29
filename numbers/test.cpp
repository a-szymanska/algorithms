#include "miller_rabin.cpp"
#include "gcd.cpp"
#include "power.cpp"
#include "equation_solver.cpp"
#include "reverse_polish_notation.cpp"

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
    assert(power(4, 24, 1000000) == 710656);
    assert(power(47, 2, 65) == 64);
    std::cout << "Power test: OK" << std::endl;
}

void test_equation_solver() {
    assert(solve(2, 4, 7) == 2);
    assert(solve(2, 1, 7) == 0);
    assert(solve(5, 7, 13) == -1);
    assert(solve(1, 1, 2) == 0);
    std::cout << "Equation solver test: OK" << std::endl;
}

void test_reverse_polish_notation() {
    std::string formula0 = "a/(b-c)", rpn_formula0 = "abc-/";
    std::vector<int> values0 = {5, 2, 3};
    assert(rpn_formula0 == convert(formula0));
    assert(calculate(rpn_formula0, values0) == -5);

    std::string formula1 = "(a+b)*c+(d-a)*(e-b)", rpn_formula1 = "ab+c*da-eb-*+";
    std::vector<int> values1 = {1, 2, 3, 4, 5};
    assert(rpn_formula1 == convert(formula1));
    assert(calculate(rpn_formula1, values1) == 18);

    std::string formula2 = "a+((c-b)/(a+b)*d-b)^b-e", rpn_formula2 = "acb-ab+/d*b-b^+e-";
    std::vector<int> values2 = {1, 2, 12, 4, 4};
    assert(rpn_formula2 == convert(formula2));
    assert(calculate(rpn_formula2, values2) == 97);
    std::cout << "Reverse Polish Notation test: OK" << std::endl;
}

int main() {
    test_miller_rabin();
    test_gcd();
    test_gcd_stein();
    test_power();
    test_equation_solver();
    test_reverse_polish_notation();
    return 0;
}