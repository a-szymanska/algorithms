#include "max_plus.cpp"
#include "convex_hull.cpp"

#include <iostream>
#include <vector>
#include <cassert>

void test_max_plus() {
    // Vertical segments: ((4,0), (4,9)), ((6,1), (6,3))
    // Horizontal segments: ((0,3), (2,3)), ((1,2), (8,2)), ((1,1), (9,1))
    int i = 0;
    std::vector<EndPoint> P = { // { id, x, y, l, type }
            {i++, 4, 0, 8, V},  // ((4,0), (4,9))
            {i++, 6, 1, 2, V},  // ((6,1), (6,3))
            {i, 0, 3, 2, L},  // ((0,3), (2,3))
            {i++, 2, 3, 2, R},
            {i, 1, 2, 7, L},  // ((1,2), (8,2))
            {i++, 8, 2, 7, R},
            {i, 1, 1, 8, L},  // ((1,1), (9,1))
            {i++, 9, 1, 8, R}
    };
    assert(max_plus(P) == 2);
    std::cout << "Max plus test: OK" << std::endl;
}

void test_convex_hull() {
    std::vector<Point> points = {
            {0, 0},
            {1, 0},
            {2, 1},
            {3, 2},
            {-1, 0},
            {-2, 1},
            {-3, 2}
    };
    std::vector<Point> hull;
    get_convex_hull(points, hull);
    std::vector<Point> hull_ok = {
            {-3, 2},
            {3, 2},
            {1, 0},
            {-1, 0}
    };
    assert(hull_ok == hull);
    std::cout << "Convex hull test: OK" << std::endl;
}

void test_convex_hull_area() {
    std::vector<Point> points = {
            {0, 0},
            {1, 0},
            {2, 1},
            {3, 2},
            {-1, 0},
            {-2, 1},
            {-3, 2}
    };
    std::vector<Point> hull;
    get_convex_hull(points, hull);
    auto area = get_area(hull);
    assert(area == 8);
    std::cout << "Convex hull area test: OK" << std::endl;
}

int main() {
    test_max_plus();
    test_convex_hull();
    test_convex_hull_area();
    return 0;
}