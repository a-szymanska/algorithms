/**
 * Algorithm to find kth element in non-decreasing order
 * in an array using the median-of-medians method.
 * Time complexity: O(n)
 */

#include <vector>

#include "insertion_sort.hpp"
#include "five_sort.hpp"

#ifndef ALGORITHMS_MEDIAN_H
#define ALGORITHMS_MEDIAN_H

/**
 * Given and array recursively find the kth element
 * @param data       array of integers
 * @param left       left index end of subarray
 * @param right      right index of subarray
 * @param k          number of element to find
 * @return           kth element from data array in non-decreasing order
 */
int get_median(std::vector<int> & data, int left, int right, int k) {
    if (right - left <= 10) {
        insertion_sort(data, left, right);
        return data[k];
    }
    std::vector<int> medians;
    for (int i = left; i <= right; i += 5) {
        if (i + 4 <= right) {
            five_sort(data, i);
            medians.push_back(data[i+2]);
        } else break;
    }

    int m = get_median(medians, 0, medians.size()-1, (right - left + 1) / 10);
    int l = left, r = right;
    for(int i = l; i <= r; i++) {
        if (data[i] < m) std::swap(data[i], data[l++]);
        else if (data[i] > m) std::swap(data[i--], data[r--]);
    }

    if (l >= k)  {
        return get_median(data, left, l, k);
    } else if (r <= k) {
        return get_median(data, r, right, k);
    }
    return m;
}

/**
 * Main function that calls the actual function performing
 * median-of-medians algorithm
 * @param data       array of integers
 * @param k          number of element to find
 * @return           kth element from data array in non-decreasing order
 */
int get_kth(std::vector<int> & data, int k) {
    int n = static_cast<int>(data.size());
    if (k < 1 || k > n) {
        return 0;
    }
    return get_median(data, 0, n-1, --k);
}

#endif //ALGORITHMS_MEDIAN_H