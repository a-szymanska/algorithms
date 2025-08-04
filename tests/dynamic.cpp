#include "../dynamic/backpack_problem.hpp"

#include <iostream>
#include <vector>
#include <cassert>

void test_backpack_problem() {
    int n = 4, max_w = 10;
    std::vector<int> weights = {3, 8, 3, 4};
    std::vector<int> values = {5, 16, 5, 7};
    std::vector<int> result = {0, 2, 3};
    assert(hirschberg(0, n-1, max_w, weights, values) == result);
    std::cout << "Backpack problem test: OK" << std::endl;
}

int main() {
    test_backpack_problem();
    return 0;
}