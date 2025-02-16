#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

// Function to check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to perform arithmetic operations
int apply_operation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b == 0) ? throw runtime_error("Error: Division by zero") : a / b;
    }
    return 0;
}

// Function to evaluate an arithmetic expression
int evaluate(string expression) {
    stack<int> values;  // Stack for numbers
    stack<char> ops;    // Stack for operators

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') continue;  // Ignore spaces

        // If the current character is a number, push it to values stack
        if (isdigit(expression[i])) {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--; // Adjust index after reading full number
        }
        // If the current character is an operator
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                values.push(apply_operation(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    // Apply remaining operations in the stack
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();

        values.push(apply_operation(val1, val2, op));
    }

    return values.top();
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression (e.g., 3 + 5 * 2): ";
    getline(cin, expression);

    try {
        int result = evaluate(expression);
        cout << "Result: " << result << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
