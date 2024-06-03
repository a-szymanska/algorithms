#include "aho_corasick_tree.h"
#include <iostream>
#include <cassert>

int main() {
    std::vector<std::string> patterns = {"berry", "mango", "pear", "peach"};
    AhoCorasickTree Tree(patterns);
    // Check if given texts contain any of the patterns
    assert(Tree.find("raspberry") == true);
    assert(Tree.find("pearl") == true);
    assert(Tree.find("apple pie") == false);
    return 0;
}