/**
 *
 * Created by Anna Szymańska on 24.11.2022
 */

#include <vector>

void swap_num(int & x, int & y);


/**
 * Sort a five-element subarray
 * @param data      array of integers that is to be sorted
 * @param l         start index of the five element subarray in the array
 */

void five_sort(std::vector<int> & data, int l = 0) {
    int l0 = l, l1 = l0 + 1, l2 = l1 + 1, l3 = l2 + 1, l4 = l3 + 1;
    if(data[l1] < data[l0]) {
        swap_num(data[l0], data[l1]);
    }
    if(data[l3] < data[l2]) {
        swap_num(data[l3], data[l2]);
    }
    if(data[l0] < data[l2]) {
        swap_num(data[l1], data[l2]);
        swap_num(data[l2], data[l3]);
    } else {
        swap_num(data[l1], data[l2]);
        swap_num(data[l0], data[l1]);
    }
    if(data[l4] < data[l1]) {
        if(data[l4] < data[l0]) {
            swap_num(data[l4], data[l3]);
            swap_num(data[l3], data[l2]);
            swap_num(data[l2], data[l1]);
            swap_num(data[l1], data[l0]);
        } else {
            swap_num(data[l4], data[l3]);
            swap_num(data[l3], data[l2]);
            swap_num(data[l2], data[l1]);
        }
    } else {
        if(data[l4] < data[l2]) {
            swap_num(data[l4], data[l3]);
            swap_num(data[l3], data[l2]);
        } else {
            swap_num(data[l4], data[l3]);
        }
    }
    if(data[l4] < data[l2]) {
        if(data[l4] < data[l1]) {
            swap_num(data[l4], data[l3]);
            swap_num(data[l3], data[l2]);
            swap_num(data[l2], data[l1]);
        } else {
            swap_num(data[l4], data[l3]);
            swap_num(data[l3], data[l2]);
        }
    } else {
        if(data[l4] < data[l3]) {
            swap_num(data[l4], data[l3]);
        }
    }
}

/**
 * Swap two integers passed by reference.
 * @param x      first operand
 * @param y      second operand
 */

void swap_num(int & x, int & y) {
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}