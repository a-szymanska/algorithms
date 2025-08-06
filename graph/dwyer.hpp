/**
 * Implementation of Dwyer's algorithm for triple order traverse
 * in a binary tree. Each non-leaf node is visited three times.
 * The algorithm modifies the tree but finally restores the original.
 * Time complexity: O(|V|)
 * Space complexity: O(1)
 */

#include <vector>

#ifndef ALGORITHMS_DWYER_H
#define ALGORITHMS_DWYER_H

typedef struct node {
    int left = 0;
    int right = 0;
} node;


/**
 * Traverse the tree in triple order
 * @param T         array of nodes
 * @param root      index of the root node
 * @return          array of indices of consecutive visited nodes
 */

std::vector<int> dwyer(std::vector<node> & T, int root) {
    std::vector<int> traverse;
    int p = root, q = -1;
    while (p != -1) {
        if (p == 0) {
            p = q;
            q = 0;
            int tmp = T[p].left;
            T[p].left = T[p].right;
            T[p].right = q;
            q = p;
            p = tmp;
        } else if (T[p].left == 0 && T[p].right == 0) {
            traverse.push_back(p);
            std::swap(p, q);
        } else {
            traverse.push_back(p);
            int tmp = T[p].left;
            T[p].left = T[p].right;
            T[p].right = q;
            q = p;
            p = tmp;
        }
    }
    return traverse;
}
#endif // ALGORITHMS_DWYER_H