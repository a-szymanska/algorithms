#include "dwyer.cpp"

#include <iostream>
#include <vector>
#include <cassert>

void test_dwyer() {
    int n = 7, root = 6;
    std::vector<node> V = {
            {0, 0},
            {3, 2},
            {0, 0},
            {0, 0},
            {5, 7},
            {0, 0},
            {1, 4},
            {0, 0}
    };
    auto traverse = dwyer(V, root);
    std::vector<int> traverse_ok = {6, 1, 3, 1, 2, 1, 6, 4, 5, 4, 7, 4, 6};
    assert(traverse == traverse_ok);
    std::cout << "Dwyer traverse test: OK" << std::endl;
}


int main() {
    test_dwyer();
    return 0;
}