#include "max_plus.cpp"
#include "convex_hull.cpp"
#include "convex_polygon_area.cpp"

#include <iostream>
#include <vector>
#include <cassert>

//void test_max_plus() {
//    int n_vertical = , n_horizontal = ;
//    std::vector<Point> P;
//    int i = 0;
//    P.push_back({i++, x, y, l, V});
//    P.push_back({i+n_vertical, x, y, l, L});
//    P.push_back({i+n_vertical, x+l, y, l, R});
//    int res = max_plus(P);
//    assert(max_plus == )
//    std::cout << "Max plus test: OK" << std::endl;
//}

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
    test_convex_hull();
    test_convex_hull_area();
    return 0;
}