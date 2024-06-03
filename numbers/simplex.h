/**
 * Implementation of the Simplex algorithm for linear programming.
 * It can be used to find maximizing or minimazing parameters
 * of a given linear function subject to linear constrains. The algorithm
 * detects the cases with unbounded solution using the Bland's rule.
 * Time complexity: = O((m choose n) * n*m)
 * Space complexity: O(n*m), for n variables and m equations
 * Created by Anna Szymańska on 02.06.2024
 */

#ifndef ALGORITHMS_SIMPLEX_H
#define ALGORITHMS_SIMPLEX_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <iomanip>
using namespace std;

class Simplex {
    vector<vector<double>> A;
    bool unbounded = false;
    int n_eq, n_var;
    vector<int> x_b, x_n;

public:
    Simplex(const vector<double> & b, const vector<double> & c, const vector<vector<double>> & M)
            : n_eq(static_cast<int>(b.size())), n_var(static_cast<int>(c.size())) {
        A.resize(n_eq+1, vector<double>(n_var+1, 0));
        for (int i = 1; i <= n_var; i++) {
            A[0][i] = c[i-1];
        }
        for (int i = 1; i <= n_eq; i++) {
            A[i][0] = b[i - 1];
            for (int j = 1; j <= n_var; j++) {
                A[i][j] = -M[i-1][j-1];
            }
        }
        for (int i = 0; i < n_var; i++) {
            x_n.push_back(i);
        }
        for (int i = 0; i < n_eq; i++) {
            x_b.push_back(i + n_var);
        }
    }

    void do_pivot(int in, int out) {
        auto alpha = A[out][in];
        for (int j = 0; j <= n_var; j++) {
            A[out][j] = -A[out][j] / alpha;
        }
        A[out][in] = 1/alpha;

        for (int i = 0; i <= n_eq; i++) {
            if (i == out) {
                continue;
            }
            auto beta = A[i][in];
            A[i][in] = 0;
            for (int j = 0; j <= n_var; j++) {
                A[i][j] += beta * A[out][j];
            }
        }
        swap(x_b[out-1], x_n[in-1]);
    }

    void maximize() {
        while (true) {
            bool done = true;
            int col = -1, row = -1;
            for (int j = 1; j <= n_var; j++) {
                if (A[0][j] > 0) {
                    col = j;
                    done = false;
                    break;
                }
            }
            if (done) {
                break;
            }
            unbounded = true;
            for (int i = 1; i <= n_eq; i++) {
                if (A[i][col] < 0) {
                    unbounded = false;
                    break;
                }
            }
            if (unbounded) {
                cout << "UNBOUNDED\n";
                return;
            }
            auto min_val = DBL_MAX;
            for (int i = 1; i <= n_eq; i++) {
                auto val = A[i][col];
                if (val < 0 && -A[i][0] / val < min_val) {
                    row = i;
                    min_val = -A[i][0] / val;
                }
            }
            do_pivot(col, row);
        }
        cout << std::fixed << std::setprecision(6);
        cout << A[0][0] << "\n";
        for (int i = 0; i < n_var; i++) {
            double val = 0.0;
            for (int j = 0; j < n_eq; j++) {
                if (x_b[j] == i) {
                    val = A[j+1][0];
                    break;
                }
            }
            cout << "x_" << i+1 << " = " << val << "\n";
        }
    }
};

#endif //ALGORITHMS_SIMPLEX_H
