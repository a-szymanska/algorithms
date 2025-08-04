#include "../number/miller_rabin.hpp"
#include "../number/gcd.hpp"
#include "../number/power.hpp"
#include "../number/discrete_log.hpp"
#include "../number/reverse_polish_notation.hpp"
#include "../number/ternary_search.hpp"
#include "../number/sat.hpp"
#include "../number/chinese_remainder_theorem.hpp"

#include <iostream>
#include <cstdint>
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
    int64_t s, t;
    assert(gcd(0, 117, s, t) == 117);
    assert(gcd(1024, 8, s, t) == 8);
    assert(gcd(120, 285, s, t) == 15);
    assert(gcd(65537, 42, s, t) == 1);
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
    assert(pow(4, 24, 1000000) == 710656);
    assert(pow(47, 2, 65) == 64);
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

void test_ternary_search() {
    // Basic quadratic function
    assert(std::abs(ternary_search(-10, 10, 1e-9,
                                   [](double x) { return -(x-2)*(x-2) + 4; }) - 4) < 1e-6);
    // Linear function
    assert(std::abs(ternary_search(0, 10, 1e-9,
                                   [](double x) { return 2*x + 3; }) - 23) < 1e-6);
    // Constant function
    assert(std::abs(ternary_search(0, 10, 1e-9,
                                   [](double x) { return 5; }) - 5) < 1e-6);
    // Custom quadratic function
    assert(std::abs(ternary_search(0, 6, 1e-9,
                                   [](double x) { return -x*x + 6*x - 5; }) - 4) < 1e-6);
    // Narrow interval
    assert(std::abs(ternary_search(1.4, 1.6, 1e-9,
                                   [](double x) { return -(x-1.5)*(x-1.5); }) - 0) < 1e-6);
    // Large interval
    assert(std::abs(ternary_search(-1000, 1000, 1e-9,
                                   [](double x) { return -x*x; }) - 0) < 1e-6);
    // Edge case with eps
    assert(std::abs(ternary_search(-10, 10, 1e-6,
                                   [](double x) { return -x*x; }) - 0) < 1e-3);
    std::cout << "Ternary search test: OK" << std::endl;
}

void test_sat() {
    std::vector<int> values;
    std::vector<int> sat_values = {1, 0, 0, 0, 0};
    std::vector<std::pair<int, int>> formula = {
            {+1, +2},
            {-1, -2},
            {+1, +5},
            {+3, -4},
            {+4, -3},
            {+3, -5}
    };
    assert(true == sat(5, values, formula));
    // Many solutions can actually be possible
    assert(sat_values == values);
    std::cout << "2-SAT test: OK" << std::endl;
}

void test_crt() {
    // 1 * x = 0 mod 3
    // 2 * x = 0 mod 4
    // 3 * x = 4 mod 5
    std::vector<int> A0 = {1, 2, 3};
    std::vector<int> B0 = {0, 0, 4};
    std::vector<int> C0 = {3, 4, 5};
    assert(18 == solve_crt(A0, B0, C0));

    // 2 * x = 1 mod 4
    // 3 * x = 4 mod 7
    std::vector<int> A1 = {2, 3};
    std::vector<int> B1 = {1, 4};
    std::vector<int> C1 = {4, 7};
    assert(-1 == solve_crt(A1, B1, C1));

    std::cout << "Chinese Remainder Theorem test: OK" << std::endl;
}


int main() {
    test_miller_rabin();
    test_gcd();
    test_gcd_stein();
    test_power();
    test_equation_solver();
    test_reverse_polish_notation();
    test_ternary_search();
    test_sat();
    test_crt();
    return 0;
}