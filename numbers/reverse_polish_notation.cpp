#include <iostream>
#include <stack>
#include <cmath>
#include <functional>
#include <array>

int priority(char op) {
    switch (op) {
        case '(': return 0;
        case ')': return 5;
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return -1;
    }
}

std::string convert(const std::string & formula) {
    std::stack<char> S;
    std::string rpn_formula;

    for(auto ch : formula) {
        if(isalpha(ch)) {
            rpn_formula += ch;
            continue;
        }
        if(priority(ch) == 5) {
            while(S.top() != '(' && !S.empty()) {
                rpn_formula += S.top();
                S.pop();
            }
            if (!S.empty()) S.pop();
            continue;
        }
        if(!S.empty() &&priority(ch) <= priority(S.top()) && priority(ch) != 0) {
            while(!S.empty() && priority(ch) <= priority(S.top())) {
                rpn_formula += S.top();
                S.pop();
            }
            S.push(ch);
            continue;
        } else {
            S.push(ch);
        }
    }
    while(!S.empty()) {
        if(S.top() != '(') {
            rpn_formula += S.top();
            S.pop();
        } else {
            S.pop();
        }
    }
    return rpn_formula;
}

int calculate(const std::string & rpn_formula, const std::vector<int> & values) {
    std::array<std::function<int(int, int)>, 60> operations{};
    operations['+' - '*'] = [](int a, int b) { return a + b; };
    operations['-' - '*'] = [](int a, int b) { return b - a; };
    operations['*' - '*'] = [](int a, int b) { return a * b; };
    operations['/' - '*'] = [](int a, int b) { return (a ? (b / a) : 0); };
    operations['^' - '*'] = [](int a, int b) { return pow(b, a); };
    std::stack<int> S;

    for(auto op : rpn_formula) {
        if(isalpha(op)) {
            S.push( values[op - 'a'] );
        } else {
            auto a = S.top(); S.pop();
            auto b = S.top(); S.pop();
            S.push(operations[op - '*'](a, b));
        }
    }
    auto res = S.top();
    S.pop();
    return res;
}