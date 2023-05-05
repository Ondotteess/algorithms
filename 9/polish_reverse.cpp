#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stack {
private:
    int size;
    int capacity;
    string* stack;

    void increase() {
        capacity *= 2;
        string* newStack = new string[capacity];

        for (int i = 0; i < size; i++) newStack[i] = stack[i];

        delete[] stack;
        stack = newStack;
    }

    void shrink() {
        capacity /= 2;
        string* newStack = new string[capacity];

        for (int i = 0; i < size; i++) newStack[i] = stack[i];

        delete[] stack;
        stack = newStack;

    }

public:
    Stack() {
        size = 0;
        capacity = 2;
        stack = new string[capacity];
    }

    void push(string value) {
        if (size == capacity) increase();
        stack[size++] = value;
    }

    string pop() {
        if (size < (capacity / 4)) shrink();
        if (size == 0) {
            cout << "Out of bounds!";
            exit(0);
        }
        return stack[--size];
    }

    string peek() {
        if (size == 0) {
            cout << "Stack is empty!";
            exit(0);
        }
        return stack[size - 1];
    }

    int empty() {
        return size == 0;
    }

    void printStack() {
        for (int i = 0; i < size; i++) cout << stack[i] << "\n";
    }


};

vector<string> parse(string input) {
    vector<string> output;
    string temp = "";
    for (auto i = 0; i < input.size(); i++) {
        char c = input[i];
        if (c >= '0' && c <= '9') {
            temp += c;
        }
        else if (c == ' ') {
            output.push_back(temp);
            temp = "";
        }
        else {
            output.push_back(temp);
            temp = c;
            output.push_back(temp);
            temp = "";
        }
    }
    output.push_back(temp);
    return output;
}

int priority(string token) {
    int priority = 0;
    if (token == "!" || token == "~")                      priority = 6;
    else if (token == "*" || token == "/" || token == "%") priority = 5;
    else if (token == "+" || token == "-")                 priority = 4;
    else if (token == "&")                                 priority = 3;
    else if (token == "^")                                 priority = 2;
    else if (token == "|")                                 priority = 1;

    return priority;
}

bool is_operator(string token) {
    vector<string> opers = { "!", "~", "*", "/", "%", "+", "-", "<<", ">>", "&", "^", "|", "||" };
    return count(opers.begin(), opers.end(), token);
}

bool is_digit(string token) {
    if (token[0] >= '0' && token[0] <= '9') return true;
    if (token[0] == '-') return is_digit(token.substr(1));
    return false;
}

string polish_inverse(vector<string> input) {
    string output = "";
    string token;
    string oper;
    Stack stack;

    while (!input.empty()) {
        token = input[0];
        if (is_digit(token)) {
            output += token;
            output += " ";
        }
        else if (is_operator(token)) {
            while (!stack.empty() && (priority(stack.peek()) >= priority(token))) {
                oper = stack.pop();
                output += oper;
                output += " ";
            }
            stack.push(token);
        }
        else if (token == "(") {
            stack.push(token);
        }
        else if (token == ")") {
            while (stack.peek() != "(") {
                oper = stack.pop();
                output += oper;
                output += " ";
            }
            stack.pop();
        }
        input.erase(input.begin());
    }
    while (!stack.empty()) {
        oper = stack.pop();
        output += oper;
        output += " ";
    }
    return output;
}

int main() {
    vector<string> input = { "((161 + 162) / (163 - 164)) * (165 - 166 + 167) + (168 * 169)", 
                             "((5 * 4) + 8) / (7 - 2) - 1", 
                             "6 + (9 * (8 / (7 - 2))) - 3", 
                             "((5 * 3) - 4) * (8 / (7 + 2)) + 2"
                             "(((2 + 4) * (6 - 1)) / (5 + 1)) - 3", 
                             "((6 * 4) / (9 - 3)) + ((7 - 5) * 3)",
                             "6 * ((7 - 3) * (8 / (5 - 2))) + 9",
                             "((8 * 2) + (9 / 3)) * ((6 - 4) * 5) - 1"
                             "((9 - 4) * 3) / (8 + (7 % 3)) + 1",
                             };

    vector<string> output = {};
    
    for (auto x : input) {
        vector<string> parsed = parse(x);
        Stack stack;

        string out = polish_inverse(parsed);
        output.push_back(out);
    }

    for (auto x : output) cout << x << endl;


}
