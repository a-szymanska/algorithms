#include "aho_corasick_tree.h"
#include <iostream>
#include <cassert>

void test_aho_corasick() {
    std::vector<std::string> patterns = {"berry", "mango", "pear", "peach"};
    AhoCorasickTree Tree(patterns);
    // Check if given texts contain any of the patterns
    assert(Tree.find("raspberry") == true);
    assert(Tree.find("pearl") == true);
    assert(Tree.find("apple pie") == false);
    std::cout << "Aho-Corasick tree test: OK" << std::endl;
}

int main() {
    test_aho_corasick();
    return 0;
}