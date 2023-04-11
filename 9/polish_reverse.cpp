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
        }  else if (c == ' ') {
            output.push_back(temp);
            temp = "";
        } else {
            output.push_back(temp);
            temp = c;
            output.push_back(temp);
            temp = "";
        }
	}
    output.push_back(temp);
	return output;
}

bool is_digit(string input) {
	for (auto i = 0; i < input.size(); i++) {
		if (input[i] <= '0' || input[i] >= '9') return false;
	}
	return true;
}

int priority(string token) {
    int priority = 0;
    if (token == "!" || token == "~")                 priority = 8;
    if (token == "*" || token == "/" || token == "%") priority = 7;
    if (token == "+" || token == "-")                 priority = 6;
    if (token == "<<" || token == ">>")               priority = 5;
    if (token == "&")                                 priority = 4;
    if (token == "^")                                 priority = 3;
    if (token == "|")                                 priority = 2;
    if (token == "||")                                priority = 1;
    
    //if (!priority) {
    //    cout << "Error: no operator";
    //    exit(0);
    //}

    return priority;
}

bool is_operator(string token) {
    vector<string> opers = { "!", "~", "*", "/", "%", "+", "-", "<<", ">>", "&", "^", "|", "||" };
    return count(opers.begin(), opers.end(), token);
}

string polish_inverse(vector<string> input) {
    string output = ""; string token; string oper; Stack stack;

    while (!input.empty()){
        token = input[0];
        if (is_digit(token)) output += token;
        if (is_operator(token)) {
            while (!stack.empty() && (priority(stack.peek()) >= priority(token))) {
                oper = stack.pop();
                output += oper;
            }
            stack.push(token);
        }
        if (token == "(") stack.push(token);
        if (token == ")") {
            while (stack.peek() != "(") {
                oper = stack.pop();
                output += oper;
            }
            stack.pop();
        }
        output += " ";
        input.erase(input.begin());
    }
    stack.printStack();
    cout << output;
    return output;
}

int main() {
    string input = "(124 + (252 - 346)) * (25 / 235 * (236 / (6123 + 26))) - ((345 * 525 + 42 - !42) % 246)";
    vector<string> parsed = parse(input);

    //for (auto x : parsed) cout << x;
    Stack stack;

    string output = polish_inverse(parsed);

    cout << endl;

}
