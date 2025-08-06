/**
 * Implementation of the insertion sort algorithm.
 * Time complexity: O(n^2)
 */

#include <vector>

#ifndef ALGORITHMS_INSERTION_SORT_H
#define ALGORITHMS_INSERTION_SORT_H

/**
 * Perform the insertion sort algorithm
 * @param data      array of integers to be sorted
 */
void insertion_sort(std::vector<int> & data, int l = 0, int r = -1) {
    int n = static_cast<int>(data.size());
    if (r != -1) {
        n = r+1;
    }
    for(int i = l+1; i < n; i++) {
        int x = data[i];
        for(int j = i-1; j >= 0; j--) {
            if(data[j+1] < data[j]) {
                data[j+1] = data[j];
                data[j] = x;
            } else {
                break;
            }
        }
    }
}

#endif //ALGORITHMS_INSERTION_SORT_H