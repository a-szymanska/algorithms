/**
 * An implementation of the quick sort algorithm in C++.
 * The algorithm uses randomization of pivot choice
 * and Lomuto's three-way partition.
 * Created by Anna Szymańska on 27.05.2023
 */

#include <vector>

void doPartition(std::vector<int> &, int, int, int &, int &);


/**
 * Perform the quicksort algorithm.
 * @param data      array of integers to be sorted
 * @param l         left index of subarray
 * @param r         right index of subarray
 */

void quick_sort(std::vector<int> & data, int lower = -1, int upper = -1) {
    if (lower == -1) {
        lower = 0;
        upper = static_cast<int>(data.size()) - 1;
    }
    int l, r;
    while (lower < upper) {
        doPartition(data, lower, upper, l, r);
        if (l - lower < upper - r) {
            quick_sort(data, lower, l - 1);
            lower = r + 1;
        } else {
            quick_sort(data, r + 1, upper);
            upper = l - 1;
        }
    }
}

void doPartition(std::vector<int> & data, int lower, int upper, int& l, int& r) {
    int pivot_idx = lower + std::rand() % (upper - lower);
    int pivot = data[pivot_idx];
    std::swap(data[pivot_idx], data[lower]);
    l = lower, r = upper;

    for(int i = l + 1 ; i <= r; i++) {
        if (data[i] < pivot) std::swap(data[i], data[l++]);
        else if (data[i] > pivot) std::swap(data[i--], data[r--]);
    }
}