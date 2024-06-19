/**
 * A simple implementation of the selection sort algorithm in C++.
 * Created on 4.11.2022
 */

#include <vector>

/**
 * Perform the selection sort algorithm
 * @param data      array of integers to be sorted
 */

void selection_sort(std::vector<int> & data) {
    int n = static_cast<int>(data.size());
    for(int i = 0; i < n; i++) {
        int min_x = data[i], min_idx = i;
        for(int j = i+1; j < n; j++) {
            if(data[j] < min_x) {
                min_x = data[j];
                min_idx = j;
            }
        }
        data[min_idx] = data[i], data[i] = min_x;
    }
}