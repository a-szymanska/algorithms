/**
 * Implementation of interval tree template for custom Value and Modifier
 * classes with any associative operation + for combining Values
 * and * for combining Modifiers and defined () operator for applying
 * the effect of Modifier on Value.
 */

#ifndef ALGORITHMS_INTERVAL_TREE_HPP
#define ALGORITHMS_INTERVAL_TREE_HPP

#include <vector>

template<typename Value, typename Modifier>
class IntervalTree {
    struct Node {
        Value val = Value();
        Modifier mod = Modifier();

        friend Value operator + (const Node& n1, const Node& n2) {
            return n1.mod(n1.val) + n2.mod(n2.val);
        }
        friend Modifier operator * (const Node& n1, const Node& n2) {
            return n1.mod * n2.mod;
        }
    };

    size_t N;
    std::vector<Node> T;

    static int left(int v) {
        return 2*v;
    }

    static int right(int v) {
        return 2*v+1;
    }

    Node query(std::size_t begin, std::size_t end, std::size_t l, std::size_t r, int v) const {
        if (end <= l || r <= begin) return {};
        if (begin <= l && r <= end) return T[v];

        Node n1 = query(begin, end, l, (l+r)/2, left(v));
        Node n2 = query(begin, end, (l+r)/2, r, right(v));
        return {n1+n2, T[v].mod};
    }

    void update(std::size_t begin, std::size_t end, Modifier modifier, std::size_t l, std::size_t r, int v) {
        if (end <= l || r <= begin) return;
        if (begin <= l && r <= end) {
            T[v].mod = modifier * T[v].mod;
            return;
        }
        T[left(v)].mod = T[v] * T[left(v)];
        T[right(v)].mod = T[v] * T[right(v)];
        update(begin, end, modifier, l, (l+r)/2, left(v));
        update(begin, end, modifier, (l+r)/2, r, right(v));
        T[v] = { T[left(v)] + T[right(v)], {} };
    }

public:
    /**
     * Construct the tree initializing all values to value
     * @param n         number of leaves, i.e. size of expected data
     * @param value     the initial value for nodes
     */
    IntervalTree(std::size_t n, Value value = {}) : N(1 << (std::__lg(n) + 1)), T(2*N) {
        Node node = {value, {}};
        std::fill(T.begin() + N, T.end(), node);
        for (int i = N-1; i > 0; i--) {
            T[i].val = T[left(i)] + T[right(i)];
        }
    }

    /**
     * Construct the tree initializing the nodes according to values
     * @param values     the initial values for nodes
     */
    IntervalTree(const std::vector<Value>& values) : N(1 << (std::__lg(values.size()) + 1)), T(2*N) {
        for (int i = 0; i < values.size(); i++) {
            T[N+i].val = values[i];
        }
        for (int i = N-1; i > 0; i--) {
            T[i].val = T[left(i)] + T[right(i)];
        }
    }

    Value query(std::size_t begin, std::size_t end) const {
        if (begin == end) return {};
        Node n = query(begin, end, 0, N, 1);
        return n.mod(n.val);
    }

    void update(std::size_t begin, std::size_t end, Modifier modifier) {
        update(begin, end, modifier, 0, N, 1);
    }
};


#endif //ALGORITHMS_INTERVAL_TREE_HPP