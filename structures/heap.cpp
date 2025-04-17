#include "heap.hpp"
#include <iostream>

template<typename T>
struct MaxCompare {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
};

template<typename T>
struct MinCompare {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs > rhs;
    }
};

int main() {
    // Max-heap test
    Heap<std::pair<int, int>, MaxCompare<std::pair<int, int>>> maxHeap;
    maxHeap.insert({1, 4});
    maxHeap.insert({2, 3});
    maxHeap.insert({0, 1});

    std::cout << "Max-heap top: " << maxHeap.top().first << ", " << maxHeap.top().second << std::endl;
    while (maxHeap.size() > 0) {
        auto p = maxHeap.pop();
        std::cout << "Popped: " << p.first << ", " << p.second << std::endl;
    }

    // Min-heap test
    Heap<std::string, MinCompare<std::string>> minHeap;
    minHeap.insert("mango");
    minHeap.insert("black berry");
    minHeap.insert("kiwi");

    std::cout << "Min-heap top: " << minHeap.top() << std::endl;
    while (minHeap.size() > 0) {
        auto p = minHeap.pop();
        std::cout << "Popped: " << p << std::endl;
    }

    return 0;
}