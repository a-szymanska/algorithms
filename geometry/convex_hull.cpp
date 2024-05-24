#include <vector>
using namespace std;

struct Point {
    long long x, y;

    bool operator==(Point const & p) const {
        return x == p.x && y == p.y;
    }
    bool operator<(Point const & p) const {
        return (y < p.y || (y == p.y && x < p.x));
    }
};

int ccw(const Point &, const Point &, const Point &);
long long dist(Point, Point);


/**
 *
 * @param P
 * @param H
 */
void get_convex_hull(vector<Point> & P, vector<Point> & H) {
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

    vector<Point> P_ncl({p_min});
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

    vector<Point> S(n_ncl);
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
 *
 * @param p
 * @param q
 * @param r
 * @return
 */
int ccw(const Point & p, const Point & q, const Point & r) {
    long long res = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (res < 0) {
        return 1;
    } else if (res > 0) {
        return -1;
    }
    return 0;
}

/**
 *
 * @param p
 * @param q
 * @return
 */
long long dist(Point p, Point q) {
    long long delta_x = (p.x - q.x);
    long long delta_y = (p.y - q.y);
    return delta_x * delta_x + delta_y * delta_y;
}
