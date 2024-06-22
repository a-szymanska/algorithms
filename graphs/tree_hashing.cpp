/**
 * Simple function to encode a tree to compare with other
 * trees for isomorphism.
 * Created on 22.06.2024
 */

#include <iostream>
#include <vector>

const size_t p = 1635795965187779;
const size_t m = 507077;

/**
 * Encode the array of numbers
 * @param part_hash     array of numbers
 * @return              encoding
 */
std::size_t get_array_hash(std::vector<size_t> & part_hash) {
    if (part_hash.empty()) {
        return 1;
    }
    std::size_t hash = 0, x = m;
    for (size_t c : part_hash) {
        hash = (hash ^ (c * x)) % p;
        x *= m;
    }
    return hash;
}

/**
 * Encode the tree structure
 * @param tree            tree structure given as array of balanced ( ) brackets
 * @param idx             current position in tree array
 * @return                encoding of the tree
 */
std::size_t get_tree_hash(const std::vector<char> & tree, int & idx) {
    idx++;
    std::vector<size_t> part_hash;
    int n = static_cast<int>(tree.size());
    while (tree[idx] == '(' && idx < n) {
        part_hash.push_back(get_tree_hash(tree, idx));
    }
    idx++;
    std::sort(part_hash.begin(), part_hash.end());
    return get_array_hash(part_hash);
}

/**
 * Main function to call the helpers
 * @param tree      tree structure given as array of balanced ( ) brackets
 * @return          encoding of the tree
 */
std::size_t hash_tree(const std::vector<char> & tree) {
    int idx = 0;
    return get_tree_hash(tree, idx);
}
