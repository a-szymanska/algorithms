/**
 * Implementation of Aho-Corasick tree for pattern
 * matching in strings.
 * Time complexity of construction: O(n)
 * Space complexity: O(n)
 * for n being the sum of lengths of all patterns
 * Created on 17.04.2024
 */

#ifndef ALGORITHMS_AHO_CORASICK_TREE_HPP
#define ALGORITHMS_AHO_CORASICK_TREE_HPP

#include <algorithm>
#include <vector>
#include <queue>

struct Node {
    int chld[26];   // size of alphabet
    bool final = false;
    int msm = -1;

    Node() {
        std::fill_n(chld, 26, -1);
    }
};

struct AhoCorasickTree {
    std::vector<Node> nodes;

    AhoCorasickTree(std::vector<std::string> & patterns) {
        nodes.emplace_back();
        for (auto p : patterns) {
            add_pattern(p);
        }
        add_msm_edges();
        add_blue_edges();

    }
    void add_pattern(std::string &str) {
        int i = 0;
        for (char ch : str) {
            int c = ch - 'a';
            if (nodes[i].chld[c] == -1) {
                nodes[i].chld[c] = static_cast<int>(nodes.size());
                nodes.emplace_back();
            }
            i = nodes[i].chld[c];
        }
        nodes[i].final = true;
    }

    void add_msm_edges() {  // mismatch links
        auto& root = nodes[0];
        root.msm = 0;
        std::queue<int> q;
        for (auto & child_idx : root.chld) {
            if (child_idx != -1) {
                auto& child = nodes[child_idx];
                child.msm = 0;
                q.push(child_idx);
            } else {
                child_idx = 0;
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (nodes[v].chld[i] != -1) {
                    int MSM = nodes[v].msm;
                    while (nodes[MSM].chld[i] == -1) {
                        MSM = nodes[MSM].msm;
                    }
                    MSM = nodes[MSM].chld[i];
                    nodes[nodes[v].chld[i]].msm = MSM;
                    nodes[nodes[v].chld[i]].final |= nodes[MSM].final;
                    q.push(nodes[v].chld[i]);
                }
            }
        }
    }

    void add_blue_edges() {
        std::queue<int> q;
        auto &root = nodes[0];
        root.msm = 0;
        for (auto child_idx : root.chld) {
            if (child_idx > 0) {
                auto &child = nodes[child_idx];
                for (int i = 0; i < 26; i++) {
                    auto &child2 = child.chld[i];
                    if (child2 == -1) {
                        child2 = nodes[child.msm].chld[i];
                    } else if (child2 != 0) {
                        q.push(child2);
                    }
                }
            }
        }
        while (!q.empty()) {
            int state = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (nodes[state].chld[i] == -1) {
                    nodes[state].chld[i] = nodes[nodes[state].msm].chld[i];
                } else {
                    q.push(nodes[state].chld[i]);
                }
            }
        }
    }

    bool find(const std::string &txt) {
        int state = 0;
        for (auto c : txt) {
            int ch = c - 'a';
            while (nodes[state].chld[ch] == -1) {
                state = nodes[state].msm;
            }
            state = nodes[state].chld[ch];
            if (nodes[state].final) {
                return true;
            }
        }
        return false;
    }
};

#endif //ALGORITHMS_AHO_CORASICK_TREE_HPP
