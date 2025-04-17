#include "double_linked_list.hpp"
#include <iostream>
#include <string>

int main() {
    DoubleList<std::string> trainA;
    trainA.push_front("a");
    trainA.push_front("b");
    trainA.push_back("c");
    std::cout << "trainA" << std::endl;
    for (const auto& x : trainA) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    trainA.reverse();
    std::cout << "trainA: reverse" << std::endl;
    for (auto x : trainA) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    DoubleList<std::string> trainB;
    trainB.push_front("A");
    trainB.push_front("B");
    trainB.push_front("C");
    std::cout << "trainB" << std::endl;
    for (const auto& x : trainB) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    trainA.merge(trainB);
    std::cout << "trainA: merge with trainB" << std::endl;
    for (auto x : trainA) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    trainA.reverse();
    std::cout << "trainA: reverse" << std::endl;
    for (auto x : trainA) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    trainA.pop_front();
    std::cout << "trainA: remove first" << std::endl;
    for (auto x : trainA) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    trainA.pop_back();
    std::cout << "trainA: remove last" << std::endl;
    for (auto x : trainA) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}