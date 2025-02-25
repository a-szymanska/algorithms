/**
 * Floor division on large number using FFT and Newton's method
 * to approximate the inverse of divisor. The code uses function
 * std::vector<int> fastmul(std::vector<int> &a, std::vector<int> &b)
 * that multiplies two numbers represented as vectors
 * and starting from the least significant figures in O(nlgn).
 *
 * Time complexity: O(n * lg^2 n) (more or less)
 * Space complexity: O(n), where n = |A| + |B|
 * Created on 25.02.2025
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
// #include "fastmul.hpp"

#ifndef ALGORITHMS_FAST_DIVISION_H
#define ALGORITHMS_FAST_DIVISION_H

std::vector<int> operator-(const std::vector<int> & vec1, std::vector<int> & vec2) {
    int n = vec1.size();
    vec2.resize(n, 0);
    std::vector<int> res(n);
    int rest = 0;
    for (int i = 0; i < n; i++) {
        int x = vec1[i] - vec2[i] - rest;
        if (x < 0) {
            x += 10;
            rest = 1;
        } else {
            rest = 0;
        }
        res[i] = x;
    }
    int i;
    for (i = n-1; i >= 0; i--) {
        if (res[i] != 0) {
            ++i;
            break;
        }
    }
    res.erase(res.begin() + i, res.end());
    return res;
}

std::vector<int> operator*(std::vector<int> vec1, std::vector<int> vec2) {
    auto res = fastmul(vec1, vec2);
    return res;
}

void fastdiv(std::vector<int> & A, std::vector<int> & B) {
    int k = 1000000, p_b = B.size() - 1, p = p_b;
    int A_size = A.size();
    std::vector<int> x(k, 0);
    x[k-1] = 1;
    int n_iter = 10 * std::log2(B.size() + 1);
    while (n_iter--) {
        auto bx = B * x;
        int p_bx = p - p_b;
        int x_size = x.size(), bx_size = bx.size();
        if (bx_size > x_size + p_b) {
            --p_bx;
        }
        std::vector<int> bx2 (p_bx + bx_size + 1, 0);
        bx2[p_bx + bx_size] = 2;
        bx2 = bx2 - bx;
        auto x_new = x * bx2;
        int x_new_size = x_new.size();
        if (x_new[x_new_size - k - 1] >= 5) {
            int up = 1;
            for (int i = x_new_size - k; i < x_new_size && up; i++) {
                up = (++x_new[i] > 9);
                x_new[i] %= 10;
            }
            if (up) {
                x_new.push_back(1);
            }
        }
        if (x_new.size() > x_size + bx2.size()) {
            --p;
        }
        std::copy(x_new.end() - k, x_new.end(), x.begin());
    }

    std::vector<int> x_round(x.end() - k, x.end());
    if (x.size() > k && x[x.size() - k - 1] >= 5) {
        x_round[0]++;
    }
    A.resize(A.size() + p + k);
    std::reverse(A.begin(), A.end());
    auto AB = A * x;
    int n_digits = (int) A_size - p;
    if (A.size() + x_round.size() != AB.size()) --n_digits;
    int res = 0, AB_size = AB.size();
    bool up = true;
    for (int i = std::max(0, AB_size - n_digits - 1); i >= std::max(AB_size - n_digits - 10, 0) && up; i--) {
        up = (AB[i] == 9);
    }
    for (int i = std::max(0, AB_size - n_digits); i < AB_size && up; i++) {
        up = (++AB[i] > 9);
        AB[i] %= 10;
    }
    if (up) {
        AB.push_back(1);
        ++AB_size;
        ++n_digits;
    }
    for (int i = AB_size - 1; i >= std::max(0, AB_size - n_digits); i--) {
        std::cout << AB[i];
    }
    std::cout << "\n";
}

#endif //ALGORITHMS_FAST_DIVISION_H