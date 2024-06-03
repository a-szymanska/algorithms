#include "simplex.h"
#include <vector>

int main() {
    // Maximize 3*x1 + x2 + 2*x3
    // Subject to:
    // x1 + x2 + 3*x3 <= 30
    // 2*x1 + 2*x2 + 5*x3 <= 24
    // 4*x1 + x2 + 2*x3 <= 36
    std::vector<std::vector<double>> M = {
            {1, 1, 3},
            {2, 2, 5},
            {4, 1, 2}
    };
    std::vector<double> b = {30, 24, 36};
    std::vector<double> c = {3, 1, 2};

    Simplex simplex(b, c, M);
    simplex.maximize();
    return 0;
}