#include <vector>
#include <algorithm>
#include <set>
#include <climits>

#define L (-1)
#define R  1
#define V  0

struct EndPoint {
    int id;
    int x, y, l;
    int type;

    friend bool operator<(const EndPoint &p1, const EndPoint &p2) {
        return p1.y < p2.y;
    }
};
bool find_plus(int, std::vector<EndPoint> &);


/**
 *
 * @param P
 * @return
 */

int max_plus(std::vector<EndPoint> & P) {
    int max_len = INT_MIN;
    for (auto p : P) {
        max_len = std::max(max_len, p.l);
    }

    int l = 0, r = max_len;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (find_plus(mid, P)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

bool find_plus(int r, std::vector<EndPoint> &P) {
    std::vector<EndPoint> Q;
    int max_id = INT_MIN;
    for (auto p : P) {
        if (p.l < 2*r) {
            continue;
        }
        max_id = std::max(max_id, p.id);
        if (p.type == L) {
            Q.push_back({p.id, p.x + r, p.y, p.l-2*r, L});
        } else if (p.type == R) {
            Q.push_back({p.id, p.x - r, p.y, p.l-2 * r, R});
        } else {
            Q.push_back({p.id, p.x, p.y + r, p.l - 2 * r, V});
        }
    }
    if (Q.empty()) {
        return false;
    }

    std::sort(Q.begin(), Q.end(), [](const EndPoint &p1, const EndPoint &p2)
    { return (p1.x < p2.x || (p1.x == p2.x && p1.type < p2.type)); });

    std::set<EndPoint> S;
    std::vector<std::set<EndPoint>::iterator> points_in_set(max_id+1);
    for (auto p : Q) {
        if (p.type == L) {
            auto it = S.insert(p);
            points_in_set[p.id] = it.first;
        } else if (p.type == R) {
            S.erase(points_in_set[p.id]);
        } else {
            auto it = S.lower_bound(p);
            if (it != S.end() && it->y <= p.y + p.l) {
                return true;
            }
        }
    }
    return false;
}

