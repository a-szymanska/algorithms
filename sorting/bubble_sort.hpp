/**
 * Implementation of the bubble sort algorithm.
 * Time complexity: O(n^2)
 */

#include <vector>

#ifndef ALGORITHMS_BUBBLE_SORT_H
#define ALGORITHMS_BUBBLE_SORT_H

/**
 * Perform the bubble sort algorithm
 * @param data      array of integers to be sorted
 */
void bubble_sort(std::vector<int> & data) {
    int x = 0, n = static_cast<int>(data.size());
    bool swap_flag = false;
    for (int j = 0; j < n - 1; j++) {
        swap_flag = false;
        for (int k = 0; k < n - 1; k++) {
            if (data[k] > data[k+1]) {
                std::swap(data[k], data[k+1]);
                swap_flag = true;
            }
        }
        if (!swap_flag) {
            break;
        }
    }
}

#endif //ALGORITHMS_BUBBLE_SORT_H