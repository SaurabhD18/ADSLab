#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void insert(Node*& head, int x, int p) {
    Node* newNode = new Node();
    newNode->data = x;
    if (p == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* temp = head;
    for (int i = 0; i < p - 1 && temp != nullptr; i++)
        temp = temp->next;
    if (!temp) {
        cout << "Invalid position\n";
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void search(Node* head, int x) {
    int pos = 0;
    while (head) {
        if (head->data == x) {
            cout << "Element found at position " << pos << "\n";
            return;
        }
        head = head->next;
        pos++;
    }
    cout << "Element not found\n";
}

void deleteElement(Node*& head, int p) {
    if (!head) {
        cout << "List is empty\n";
        return;
    }
    if (p == 0) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        return;
    }
    Node* temp = head;
    for (int i = 0; i < p - 1 && temp->next != nullptr; i++)
        temp = temp->next;
    if (!temp->next) {
        cout << "Invalid position\n";
        return;
    }
    Node* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
}

int main() {
    Node* head = nullptr;

    insert(head, 10, 0); // Insert
    insert(head, 20, 1); // Insert
    search(head, 20);    // Search
    deleteElement(head, 1); // Delete
    return 0;
}
