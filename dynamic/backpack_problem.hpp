/**
 * Implementation of backpack problem with restoration
 * of optimal solution using the Hirschberg's method
 * based on divide and conquer strategy.
 * Time complexity: O(n*w)
 * Space complexity: O(w)
 * Created on 10.10.2023
 */

#include <vector>


#ifndef ALGORITHMS_BACKPACK_H
#define ALGORITHMS_BACKPACK_H

std::vector<int> chosen_objects;

/**
 * Perform the backpack algorithm - find the maximal value
 * of objects chosen with limited total weight
 * @param l            left index of considered subarray
 * @param r            right index of considered subarray
 * @param max_w        maximum possible weight
 * @param weights      input weights of objects
 * @param values       input values of objects
 * @return             maximum possible values choosing from all n objects
 *                     with limited weight
 */
std::vector<int> pack(int l, int r, int max_w, std::vector<int> & weights, std::vector<int> & values) {
    std::vector<int> dp(max_w + 1, 0);
    for (int i = l; i <= r; i++) {
        for (int w = max_w; w >= weights[i]; w--) {
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return dp;
}

/**
 * Find best partition index for Hirschberg's algorithm
 * @param max_w      maximum possible weight
 * @param dp1        results of pack function for the first half
 * @param dp2        results of pack function for the second half
 * @return           optimal index of partition
 */
int find_opt(int max_w, std::vector<int>& dp1, std::vector<int>& dp2) {
    int opt_i = 0, max_v = INT_MIN;
    for (int i = 0; i <= max_w; i++) {
        if (dp1[i] + dp2[max_w - i] > max_v) {
            opt_i = i;
            max_v = dp1[i] + dp2[max_w - i];
        }
    }
    return opt_i;
}

/**
 * Perform Hirschberg's algorithm to solve the backpack problem
 * and restore the solution
 * @param l            left index of considered subarray
 * @param r            right index of considered subarray
 * @param max_w        maximum possible weight
 * @param weights      input weights of objects
 * @param values       input values of objects
 * @return
 */
std::vector<int> & hirschberg(int l, int r, int max_w, std::vector<int> & weights, std::vector<int> & values) {
    if (l == r) {
        if (weights[l] <= max_w) {
            chosen_objects.push_back(l);
        }
        return chosen_objects;
    } else if (r - l >= 1) {
        int mid = l + (r - l) / 2;
        auto dp1 = pack(l, mid, max_w, weights, values);
        auto dp2 = pack(mid + 1, r, max_w, weights, values);
        int opt_i = find_opt(max_w, dp1, dp2);
        hirschberg(l, mid, opt_i, weights, values);
        hirschberg(mid + 1, r, max_w - opt_i, weights, values);
    }
    return chosen_objects;
}

#endif //ALGORITHMS_BACKPACK_H