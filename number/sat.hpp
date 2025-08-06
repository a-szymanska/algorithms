/**
 * The algorithm to find the solution for the boolean formula
 * in 2-CNF form or decide that it is unsatisfiable.
 * Time complexity: O(n)
 * Space complexity: O(n)
 */

#include <vector>
#include <stack>
#include <climits>
#include <functional>

#ifndef ALGORITHMS_SAT_H
#define ALGORITHMS_SAT_H

#define WHITE 0
#define GRAY 1
#define BLACK 2

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
    std::vector<int> time_in(2*n+2, INT_MAX), low(2*n+2, INT_MAX), color(2*n+2, WHITE), component(2*n+2, -1);

    std::function<void(int)> get_colors = [&](int x) {
        time_in[x+n] = low[x+n] = timestamp++;
        color[x+n] = GRAY;
        S.push(x);
        for (int y : adj[x+n]) {
            if (color[y+n] == WHITE) {
                get_colors(y);
                low[x+n] = std::min(low[x+n], low[y+n]);
            } else if (color[y+n] == GRAY) {
                low[x+n] = std::min(low[x+n], time_in[y+n]);
            }
        }

        if (low[x+n] == time_in[x+n]) {
            while (S.top() != x) {
                int y = S.top();
                S.pop();
                component[y+n] = comp;
                color[y+n] = BLACK;
            }
            S.pop();
            component[x+n] = comp;
            color[x+n] = BLACK;
            comp++;
        }
    };

    for (int x = -n; x <= n; x++) {
        if (color[x+n] == WHITE) {
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


#endif //ALGORITHMS_SAT_H