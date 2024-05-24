/**
 * A simple implementation of the insertion sort algorithm in C++.
 * Created by Anna Szymańska on 4.11.2022
 */

#include <vector>

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