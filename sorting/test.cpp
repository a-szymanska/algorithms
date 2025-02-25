#include "bubble_sort.hpp"
#include "selection_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "five_sort.hpp"
#include "find_kth.hpp"

#include <iostream>
#include <cassert>

void test_bubble_sort() {
    std::vector<int> data = {0, 2, 1, 3, 4, 0, 0};
    std::vector<int> sorted_data = {0, 0, 0, 1, 2, 3, 4};
    bubble_sort(data);
    assert(sorted_data == data);
    std::cout << "Bubble sort: OK" << std::endl;
}

void test_selection_sort() {
    std::vector<int> data = {0, 2, 1, 3, 4, 0, 0};
    std::vector<int> sorted_data = {0, 0, 0, 1, 2, 3, 4};
    selection_sort(data);
    assert(sorted_data == data);
    std::cout << "Selection sort: OK" << std::endl;
}

void test_insertion_sort() {
    std::vector<int> data = {0, 2, 1, 3, 4, 0, 0};
    std::vector<int> sorted_data = {0, 0, 0, 1, 2, 3, 4};
    insertion_sort(data);
    assert(sorted_data == data);
    std::cout << "Insertion sort: OK" << std::endl;
}

void test_merge_sort_inversion_count() {
    std::vector<int> data = {0, 2, 1, 3, 4, 0, 0};
    std::vector<int> sorted_data = {0, 0, 0, 1, 2, 3, 4};
    auto count = merge_sort(data);
    assert(sorted_data == data);
    assert(count == 9);
    std::cout << "Merge sort: OK" << std::endl;
}

void test_quick_sort() {
    std::vector<int> data = {0, 2, 1, 3, 4, 0, 0};
    std::vector<int> sorted_data = {0, 0, 0, 1, 2, 3, 4};
    quick_sort(data);
    assert(sorted_data == data);
    std::cout << "Quick sort: OK" << std::endl;
}

void test_five_sort() {
    std::vector<int> data0 = {0, 2, 1, 3, 0};
    std::vector<int> sorted_data0 = {0, 0, 1, 2, 3};
    five_sort(data0);
    assert(sorted_data0 == data0);
    std::vector<int> data1 = {0, 2, 1, 3, 0, 4, 5, 0, 1};
    std::vector<int> sorted_data1 = {0, 2, 0, 1, 3, 4, 5, 0, 1};
    five_sort(data1, 2);
    assert(sorted_data1 == data1);
    std::cout << "Five sort: OK" << std::endl;
}

void test_find_kth() {
    std::vector<int> data = {0, 1, 2, 3, 1, 1, 0, 4, 0};
    int n = static_cast<int>(data.size()), k = 7;
    int k_element = get_kth(data, k);
    assert(k_element == 2);
}

int main() {
    test_bubble_sort();
    test_selection_sort();
    test_insertion_sort();
    test_merge_sort_inversion_count();
    test_quick_sort();
    test_five_sort();
    test_find_kth();
    return 0;
}