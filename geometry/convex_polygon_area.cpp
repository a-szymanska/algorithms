// Point defined in convex_hull.cpp

long long get_area(vector<Point> & P) {
    int n = P.size();
    long long area = 0;
    for (int i = 0, j = n-1; i < n; j=i, i++) {
        area += (P[j].x + P[i].x) * (P[j].y - P[i].y);
    }
    return area >> 1;
}