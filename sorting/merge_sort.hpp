/**
 * Implementation of the merge sort algorithm.
 * The merge_sort function additionally counts the number
 * of inversions in the sequence of number.
 * Time complexity: O(n*logn)
 */

#include <vector>

#ifndef ALGORITHMS_MERGE_SORT_H
#define ALGORITHMS_MERGE_SORT_H

int merge(std::vector<int> &, int, int);

/**
 * Perform the merge sort algorithm recursively
 * @param data      array of integers to be sorted
 * @param l         left index of subarray
 * @param r         right index of subarray
 * @return          number of inversions
 */
int merge_sort(std::vector<int> & data, int l = -1, int r = -1) {
    if (l == -1) {
        l = 0; r = static_cast<int>(data.size()) - 1;
    }
    int inv_cnt = 0;
    if (l < r) {
        int m = (l+r) / 2;

        inv_cnt += merge_sort(data, l, m);
        inv_cnt += merge_sort(data, m + 1, r);
        inv_cnt += merge(data, l, r);
    }
    return inv_cnt;
}

/**
 * Merge two sorted arrays and count inversions
 * @param data      vector of integers to be sorted
 * @param l         left index of subarray
 * @param r         right index of subarray
 * @return          number of inversions
 */
int merge(std::vector<int> & data, int l, int r) {
    int m = (r-l) / 2;
    std::vector<int> tmp(r-l+1);
    for (int i = l; i <= r; i++)  {
        tmp[i-l] = data[i];
    }
    r -= l;
    int idx, i, j, inv_cnt = 0;
    for (idx = l, i = 0, j = m+1; i <= m && j <= r; idx++) {
        if (tmp[i] <= tmp[j]) {
            data[idx] = tmp[i++];
        } else {
            data[idx] = tmp[j++];
            inv_cnt += m - i + 1;
        }
    }
    while (i <= m) {
        data[idx++] = tmp[i++];
    }
    while (j <= r) {
        data[idx++] = tmp[j++];
    }
    return inv_cnt;
}

#endif //ALGORITHMS_MERGE_SORT_H