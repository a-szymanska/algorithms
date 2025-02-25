#include "pref_suf.hpp"
#include <iostream>
#include <cassert>

void test_lps() {
    std::vector<char> txt0 = {'a', 'a', 'a', 'a'};
    std::vector<int> pref_suf0 = {-1, 0, 1, 2, 3};
    assert(pref_suf0 == get_lps(txt0));

    std::vector<char> txt1 = {'a', 'b', 'c', 'a', 'b', 'a', 'd'};
    std::vector<int> pref_suf1 = {-1, 0, 0, 0, 1, 2, 1, 0};
    assert(pref_suf1 == get_lps(txt1));

    std::vector<char> txt2 = {};
    std::vector<int> pref_suf2 = {-1};
    assert(pref_suf2 == get_lps(txt2));

    std::cout << "Prefix-suffix test: OK" << std::endl;
}

void test_kmp() {
    std::vector<char> pat = {'a', 'b'};
    std::vector<char> txt = {'a', 'b', 'a', 'a', 'b', 'a', 'd'};
    std::vector<int> matches = {0, 3};
    assert(matches == kmp(pat, txt));

    std::cout << "KMP test: OK" << std::endl;
}

int main() {
    test_lps();
    test_kmp();
    return 0;
}