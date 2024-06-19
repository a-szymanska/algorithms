#include "unordered_map.h"


#include <iostream>
#include "unordered_map.h"

int main() {
    UnorderedMap<int, std::string> map;

    // Insert some pairs
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});
    map[4] = "four";
    map[5] = "five";
    // Modify an element
    map[2] = "TWO";

    for (const auto & x : map) {
        std::cout << x.first << ": " << x.second << std::endl;
    }

    // Check if an element is in the map
    if (map.find(3) != map.end()) {
        std::cout << "Element 3 found: " << map[3] << std::endl;
    } else {
        std::cout << "Element 3 not found" << std::endl;
    }

    // Erase some elements
    map.erase(3);
    UnorderedMap<int, std::string>::Iterator it = map.find(4);
    if (it != map.end()) {
        map.erase(it);
    }
    for (const auto & x : map) {
        std::cout << x.first << ": " << x.second << std::endl;
    }

    // Clean map
    map.clear();
    if (map.size() == 0) {
        std::cout << "Map is empty" << std::endl;
    }

    return 0;
}
