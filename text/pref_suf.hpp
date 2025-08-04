/**
 * The LPS array and Knuth-Morris-Pratt algorithm
 * for pattern searching in text.
 * Time complexity: O(|text| + |pattern|)
 * Space complexity: O(|text|)
 * Created on 22.06.2024
 */

#include <vector>

#ifndef ALGORITHMS_PREF_SUF_H
#define ALGORITHMS_PREF_SUF_H

/**
 * Get the longest prefix-suffix array
 * @param txt       text as array
 * @return          array with length of maximum proper prefix
 *                  that is also the suffix of txt[0...i-1]
 */
std::vector<int> get_lps(const std::vector<char>& txt) {
    int n = static_cast<int>(txt.size());
    std::vector<int> P(n+1);
    int t;
    t = P[0] = -1;
    for (int i = 0; i < n; i++) {
        while (t != -1 && txt[t] != txt[i]) {
            t = P[t];
        }
        P[i + 1] = ++t;
    }
    return P;
}

/**
 * Find all occurrences of pattern in text
 * @param pat       patter as array
 * @param txt       text as array
 * @return          starting positions of all found occurrences
 */
std::vector<int> kmp(const std::vector<char> & pat, const std::vector<char> & txt) {
    int n = static_cast<int>(txt.size());
    int m = static_cast<int>(pat.size());
    std::vector<int> matches;
    auto lps_pat = get_lps(pat);

    int i = 0, j = 0;
    while (i - j <= n - m) {
        if (pat[j] == txt[i]) {
            i++; j++;
        }
        if (j == m) {
            matches.push_back(i - j);
            j = lps_pat[j];
        } else if (i < n && pat[j] != txt[i]) {
            j = lps_pat[j];
            if (j < 0) {
                i++; j++;
            }
        }
    }
    return matches;
}

#endif //ALGORITHMS_PREF_SUF_H