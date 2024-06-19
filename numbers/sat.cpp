/**
 * The algorithm to find the solution for the boolean formula
 * in 2-CNF form or decide that it is unsatisfiable.
 * Time complexity: O(n)
 * Space complexity: O(n)
 * Created on 10.03.2023
 */

#include <vector>
#include <stack>
#include <functional>

#define W 0
#define G 1
#define B 2


/**
 * Find the satisfying assignment for the given boolean formula or decide
 * that it is unsatisfiable.
 * @param n         number of variables
 * @param values    array for the satisfying assignment
 * @param formula   pairs of literals for each clause (negative for negation)
 * @return          true if the formula is satisfiable else false
 */
bool sat(int n, std::vector<int> & values, const std::vector<std::pair<int, int>> & formula) {
    values.resize(n);
    std::vector<std::vector<int>> adj(2*n+2);
    for (auto clause : formula) {
        int x = clause.first, y = clause.second;
        adj[-x+n].push_back(y);
        adj[-y+n].push_back(x);
    }
    std::stack<int> S;
    int timestamp = 0, comp = 1;
    std::vector<int> time_in(2*n+2, INT_MAX), low(2*n+2, INT_MAX), color(2*n+2, W), component(2*n+2, -1);

    std::function<void(int)> get_colors = [&](int x) {
        time_in[x+n] = low[x+n] = timestamp++;
        color[x+n] = G;
        S.push(x);
        for (int y : adj[x+n]) {
            if (color[y+n] == W) {
                get_colors(y);
                low[x+n] = std::min(low[x+n], low[y+n]);
            } else if (color[y+n] == G) {
                low[x+n] = std::min(low[x+n], time_in[y+n]);
            }
        }

        if (low[x+n] == time_in[x+n]) {
            while (S.top() != x) {
                int y = S.top();
                S.pop();
                component[y+n] = comp;
                color[y+n] = B;
            }
            S.pop();
            component[x+n] = comp;
            color[x+n] = B;
            comp++;
        }
    };

    for (int x = -n; x <= n; x++) {
        if (color[x+n] == W) {
            get_colors(x);
        }
    }

    for (int x = 1; x <= n; x++) {
        if (component[x+n] == component[-x+n]) {
            return false;
        }
    }
    for (int x = 1; x <= n; x++) {
        values[x-1] = (component[x+n] < component[-x+n] ? 1 : 0);
    }
    return true;
}
