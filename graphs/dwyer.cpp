/**
 *
 * Created by Anna Szymańska on 23.03.2023
 */

#include <vector>

typedef struct node {
    int left = 0;
    int right = 0;
} node;


/**
 *
 * @param V
 * @param root
 * @return
 */

std::vector<int> dwyer(std::vector<node> & V, int root) {
    std::vector<int> traverse;
    int p = root, q = -1;
    while (p != -1) {
        if (p == 0) {
            p = q;
            q = 0;
            int tmp = V[p].left;
            V[p].left = V[p].right;
            V[p].right = q;
            q = p;
            p = tmp;
        } else if (V[p].left == 0 && V[p].right == 0) {
            traverse.push_back(p);
            std::swap(p, q);
        } else {
            traverse.push_back(p);
            int tmp = V[p].left;
            V[p].left = V[p].right;
            V[p].right = q;
            q = p;
            p = tmp;
        }
    }
    return traverse;
}