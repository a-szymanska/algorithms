/**
 * An implementation of the ternary search algorithm.
 * Time complexity: O(log(n))
 * Space complexity: O(1)
 * Created by Anna Szymańska on 24.11.2022
 */

#include <functional>

/**
 * Perform ternary search
 * @param l         lower bound
 * @param r         upper bound
 * @param eps       accuracy
 * @param f         transformation function
 * @return          result of the search
 */
double ternary_search(double l, double r, double eps = 1e-9,
                      std::function<double(double)> f = [](double x) { return x; }) {
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);      // evaluates the function at m1
        double f2 = f(m2);      // evaluates the function at m2
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return f(l);                // return the maximum of f(x) in [l, r]
}