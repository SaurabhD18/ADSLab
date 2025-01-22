// Use the stract abstract data type to solve the parenthisis matching problem, where the input is a string of parenthesis and the output is a boolean value indicating whether the parenthesis are matched or not.

#include <iostream>
#include <string>

// implement the stack using the linked list
class Stack {
    private:
        struct Node {
            char data;
            Node* next;
        };
        Node* top;
    public:
        Stack() {
            top = NULL;
        }
        void push(char data) {
            Node* newNode = new Node;
            newNode->data = data;
            newNode->next = top;
            top = newNode;
        }
        char pop() {
            if (top == NULL) {
                return '\0';
            }
            Node* temp = top;
            top = top->next;
            char data = temp->data;
            delete temp;
            return data;
        }
        char peek() {
            if (top == NULL) {
                return '\0';
            }
            return top->data;
        }
        bool isEmpty() {
            return top == NULL;
        }
};

using namespace std;

bool isMatched(string str) {
    // consider string consisting of {}[]() characters
    Stack stack;
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (ch == '{' || ch == '[' || ch == '(') {
            stack.push(ch);
        } else if (ch == '}' || ch == ']' || ch == ')') {
            if (stack.isEmpty()) {
                return false;
            }
            char top = stack.pop();
            if ((ch == '}' && top != '{') || (ch == ']' && top != '[') || (ch == ')' && top != '(')) {
                return false;
            }
        }
    }
    return stack.isEmpty();
}

int main() {
    string str;
    cout << "Enter the string of parenthesis: ";
    cin >> str;
    
    if(isMatched(str)) {
        cout << "The parenthesis are matched." << endl;
    } else {
        cout << "The parenthesis are not matched." << endl;
    }
    return 0;
}


// Name the data structure used to solve the above problem
// :- Stack, Linked List, Node

