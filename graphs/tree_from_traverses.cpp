/**
 * Algorithm to reconstruct a binary tree given two traversals:
 * inorder and preorder or post-order. From preorder and postorder
 * one can only get back the tree if it's a full binary tree.
 * Time complexity: O(nlgn) reduced by searching for node from tho ends of array
 * Space complexity: O(n)
 * Created on 12.03.2023
 */

#include <iostream>
#include <vector>

struct Node {
    int id;
    int left;
    int right;
};

/**
 * Construct binary tree from postorder and inorder traverses
 * @param V
 * @param post      postorder
 * @param in        inorder
 * @param n
 * @return
 */
int get_post_in(std::vector<Node> & V, const std::vector<int>::iterator & post, const std::vector<int>::iterator & in, int n) {
    if (n == 0) {
        return -1;
    }
    if (n == 1) {
        V.push_back({*post, -1, -1});
        return V.size()-1;
    }
    int root = *(post + n - 1);
    int i = 0;
    for (; i < n; i++) {
        if (in[i] == root) {
            break;
        }
        if (in[n-i-1] == root) {
            i = n - i - 1;
            break;
        }
    }
    int left = get_post_in(V, post, in, i), right = get_post_in(V, post+i, in+i+1, n-i-1);
    V.push_back({root, left, right});
    return V.size() - 1;
}

int get_pre_in(std::vector<Node> & V, const std::vector<int>::iterator & pre, const std::vector<int>::iterator & in, int n) {
    if (n == 0) {
        return -1;
    }
    if (n == 1) {
        V.push_back({*pre, -1, -1});
        return V.size()-1;
    }
    int i = 0;
    int root = *pre;
    for (i; i < n; i++) {
        if (*(in + i) == root) {
            break;
        }
        if (*(in + n - i - 1) == root) {
            i = n - i - 1;
            break;
        }
    }
    int left = get_pre_in(V, pre+1, in, i), right = get_pre_in(V, pre+i+1, in+i+1, n-i-1);
    V.push_back({root, left, right});
    return V.size() - 1;
}
