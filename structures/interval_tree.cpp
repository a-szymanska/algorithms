#include "interval_tree.hpp"

#include <iostream>
#include <vector>

class Value {
public:
    int val;
    Value(int v = 0) : val(v) { }
    Value operator+(const Value& other) const {
        return Value(val + other.val);
    }
};

class Modifier {
public:
    int mod;
    Modifier(int m = 1) : mod(m) { }
    Modifier operator*(const Modifier& other) const {
        return Modifier(mod * other.mod);
    }
    Value operator()(const Value& v) const {
        return Value(v.val * mod);
    }
};

int main() {
    std::vector<Value> initial_values = {1, 2, 3, 4, 5};
    IntervalTree<Value, Modifier> tree(initial_values);

    // Query again the sum of the range [1, 4)
    Value result = tree.query(1, 4);
    std::cout << "Query [1, 4): " << result.val << std::endl;  // Expected output: 9 (2 + 3 + 4)

    // Update the range [2, 5) with a multiplier of 2
    tree.update(2, 5, Modifier(2));

    // Query again the sum of the range [1, 4)
    result = tree.query(1, 4);
    std::cout << "Query [1, 4): " << result.val << std::endl;  // Expected output: 16 (2 + 6 + 8)

    return 0;
}