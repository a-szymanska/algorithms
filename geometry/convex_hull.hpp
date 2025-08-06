/**
 * Implementation of the Graham's scan algorithm
 * and a function to calculate the area of a convex polygon.
 * Time complexity: O(n*lg(n))
 * Space complexity: O(n)
 */

#include <vector>
#include <stack>

#ifndef ALGORITHMS_CONVEX_HULL_H
#define ALGORITHMS_CONVEX_HULL_H

struct Point {
    int x, y;
    bool operator==(Point const & p) const {
        return x == p.x && y == p.y;
    }
    bool operator<(Point const & p) const {
        return (y < p.y || (y == p.y && x < p.x));
    }
};

int ccw(const Point &, const Point &, const Point &);
int dist(Point, Point);

/**
 * From those given, choose the points that form a convex hull
 * @param P     array of Points
 * @param H     array to store the hull
 */
void get_convex_hull(std::vector<Point> & P, std::vector<Point> & H) {
    int n = static_cast<int>(P.size());
    Point p_min = P[0];
    int idx_min = 0;
    for (int i = 0; i < n; i++) {
        if (P[i] < p_min) {
            p_min = P[i];
            idx_min = i;
        }
    }
    auto p_tmp = P[0];
    P[0] = P[idx_min];
    P[idx_min] = p_tmp;
    auto compare = [&](const Point &p, const Point &q) -> int {
        int c = ccw(p_min, p, q);
        return (c == 1) || (c == 0 && dist(p_min, q) >= dist(p_min, p));
    };
    sort(P.begin()+1, P.end(), compare);

    std::vector<Point> P_ncl({p_min});
    for (int i = 1; i < n; i++) {
        for (; i < n-1; i++) {
            if (ccw(p_min, P[i], P[i+1]) != 0) {
                break;
            }
        }
        P_ncl.push_back(P[i]);
    }
    int n_ncl = static_cast<int>(P_ncl.size());
    if (n_ncl < 3) {
        return;
    }
    std::vector<Point> S(n_ncl);
    int n_stack = 3;
    S[0] = P_ncl[0];
    S[1] = P_ncl[1];
    S[2] = P_ncl[2];
    for (int i = 3; i < n_ncl; i++) {
        while (n_stack > 1 && ccw(S[n_stack-2], S[n_stack-1], P_ncl[i]) != 1) {
            n_stack--;
        }
        S[n_stack++] = P_ncl[i];
    }
    for (int i = n_stack-1; i >= 0; i--) {
        H.push_back(S[i]);
    }
}

/**
 * Determine the counter-clockwise direction of r respective to p-q vector
 * @param p     first point
 * @param q     second point
 * @param r     third point
 * @return
 */
int ccw(const Point & p, const Point & q, const Point & r) {
    int res = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (res < 0) {
        return 1;
    } else if (res > 0) {
        return -1;
    }
    return 0;
}

/**
 * Calculate euclidean distance between points p and q
 * @param p     first point
 * @param q     second point
 * @return
 */
int dist(Point p, Point q) {
    int delta_x = (p.x - q.x);
    int delta_y = (p.y - q.y);
    return delta_x * delta_x + delta_y * delta_y;
}

/**
 * Calculate the area of a convex polygon
 * @param P     array of polygon vertices sorted by ccw
 * @return
 */
int get_area(std::vector<Point> & P) {
    int n = static_cast<int>(P.size());
    int area = 0;
    for (int i = 0, j = n-1; i < n; j=i, i++) {
        area += (P[j].x + P[i].x) * (P[j].y - P[i].y);
    }
    return area >> 1;
}

#endif //ALGORITHMS_CONVEX_HULL_H