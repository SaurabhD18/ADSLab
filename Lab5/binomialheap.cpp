#include <iostream>
#include <climits>
using namespace std;

// Structure of a Binomial Heap Node
struct BinomialNode {
    int key;
    int degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;

    BinomialNode(int val) {
        key = val;
        degree = 0;
        parent = child = sibling = nullptr;
    }
};

// Class for Binomial Heap
class BinomialHeap {
private:
    BinomialNode* head;

    // Merging two Binomial Trees of the same degree
    BinomialNode* mergeTrees(BinomialNode* b1, BinomialNode* b2) {
        if (b1->key > b2->key)
            swap(b1, b2);
        b2->parent = b1;
        b2->sibling = b1->child;
        b1->child = b2;
        b1->degree++;
        return b1;
    }

    // Merging two Binomial Heaps
    BinomialNode* mergeHeaps(BinomialNode* h1, BinomialNode* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        
        BinomialNode* newHead = nullptr;
        BinomialNode** pos = &newHead;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                *pos = h1;
                h1 = h1->sibling;
            } else {
                *pos = h2;
                h2 = h2->sibling;
            }
            pos = &((*pos)->sibling);
        }
        *pos = (h1) ? h1 : h2;
        return newHead;
    }

    // Consolidate trees of the same degree ;- Union of two Binomial Heaps :- The ones created by mergeTrees of Old binomial heap and new binomial heap
    void consolidate() {
        if (!head) return;
        BinomialNode* prev = nullptr;
        BinomialNode* curr = head;
        BinomialNode* next = curr->sibling;

        while (next) {
            if ((curr->degree != next->degree) || (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    mergeTrees(curr, next);
                } else {
                    if (!prev) head = next;
                    else prev->sibling = next;
                    mergeTrees(next, curr);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
    }

public:
    BinomialHeap() { head = nullptr; }

    // Insert a key into the Binomial Heap
    void insert(int key) {
        BinomialHeap tempHeap;
        tempHeap.head = new BinomialNode(key);
        head = mergeHeaps(head, tempHeap.head);
        consolidate();
    }

    // Find the minimum key
    int findMin() {
        if (!head) return INT_MAX;
        BinomialNode* minNode = head;
        BinomialNode* temp = head;
        int minKey = head->key;

        while (temp) {
            if (temp->key < minKey) {
                minKey = temp->key;
                minNode = temp;
            }
            temp = temp->sibling;
        }
        return minKey;
    }

    // Unite with another Binomial Heap
    void unite(BinomialHeap& other) {
        head = mergeHeaps(head, other.head);
        consolidate();
    }

    // Extract minimum key
    int extractMin() {
        if (!head) return INT_MAX;

        BinomialNode* minNode = head;
        BinomialNode* prevMin = nullptr;
        BinomialNode* temp = head;
        BinomialNode* prev = nullptr;
        int minKey = head->key;

        while (temp) {
            if (temp->key < minKey) {
                minKey = temp->key;
                minNode = temp;
                prevMin = prev;
            }
            prev = temp;
            temp = temp->sibling;
        }

        if (prevMin) prevMin->sibling = minNode->sibling;
        else head = minNode->sibling;

        BinomialNode* child = minNode->child;
        BinomialNode* revChild = nullptr;
        while (child) {
            BinomialNode* next = child->sibling;
            child->sibling = revChild;
            child->parent = nullptr;
            revChild = child;
            child = next;
        }

        BinomialHeap tempHeap;
        tempHeap.head = revChild;
        unite(tempHeap);

        delete minNode;
        return minKey;
    }

    // Decrease a key
    void decreaseKey(BinomialNode* node, int newKey) {
        if (!node || newKey > node->key) return;

        node->key = newKey;
        BinomialNode* temp = node;
        BinomialNode* parent = node->parent;

        while (parent && temp->key < parent->key) {
            swap(temp->key, parent->key);
            temp = parent;
            parent = parent->parent;
        }
    }

    // Delete a key
    void deleteKey(int key) {
        BinomialNode* temp = head;
        while (temp) {
            if (temp->key == key) {
                decreaseKey(temp, INT_MIN);
                extractMin();
                return;
            }
            temp = temp->sibling;
        }
    }

    // Print heap (utility function)
    void printHeap(BinomialNode* h) {
        if (!h) return;
        cout << h->key << " ";
        printHeap(h->child);
        printHeap(h->sibling);
    }

    void display() {
        cout << "Heap: ";
        printHeap(head);
        cout << endl;
    }
};

// Driver function
int main() {
    BinomialHeap heap;
    int choice, key;
    while (true) {
        cout << "\n1. Insert\n2. Find Min\n3. Extract Min\n4. Delete Key\n5. Display Heap\n6. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                heap.insert(key);
                break;
            case 2:
                cout << "Minimum key: " << heap.findMin() << endl;
                break;
            case 3:
                cout << "Extracted Min: " << heap.extractMin() << endl;
                break;
            case 4:
                cout << "Enter key to delete: ";
                cin >> key;
                heap.deleteKey(key);
                break;
            case 5:
                heap.display();
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
