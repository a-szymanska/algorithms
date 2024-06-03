/**
 * Implementation of a templated heap class with custom comparator for
 * defining the ordering of elements. The heap can be used as a min-heap
 * or a max-heap or any other depending on the comparator provided. The class
 * supports basic heap operations such as insertion, extraction of the top
 * element, and peeking at the top element.
 * Created by Anna Szymańska on 02.06.2023
 */

#ifndef ALGORITHMS_HEAP_H
#define ALGORITHMS_HEAP_H

#include <utility>
#include <functional>
#include <vector>
#include <stdexcept>

template<typename T, typename Compare = std::less<T>>
class Heap {
    std::vector<T> H;
    int _size = 0;
    Compare compare;

public:
    Heap() : H(8), compare(Compare()) { }
    explicit Heap(int capacity, Compare comp = Compare()) : H(capacity), compare(comp) { }

    int size() const {
        return _size;
    }

    void makeHeap(int i) {
        int max_i = i;
        while (2*i+1 < _size) {
            if (compare(H[max_i], H[2*i+1])) {
                max_i = 2*i+1;
            }
            if (2*i+2 < _size && compare(H[max_i], H[2*i+2])) {
                max_i = 2*i+2;
            }
            if (compare(H[i], H[max_i])) {
                std::swap(H[i], H[max_i]);
                i = max_i;
            } else break;
        }
    }

    T pop() {
        if (_size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        T root = H[0];
        H[0] = H[--_size];
        makeHeap(0);
        return root;
    }

    T top() const {
        if (_size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        return H[0];
    }

    void insert(T key) {
        if (_size == H.size()) {
            H.resize(_size * 2);
        }
        H[_size] = key;
        int i = _size++;
        while (i > 0 && compare(H[(i-1)/2], H[i])) {
            std::swap(H[i], H[(i-1)/2]);
            i = (i-1)/2;
        }
    }
};

#endif //ALGORITHMS_HEAP_H
