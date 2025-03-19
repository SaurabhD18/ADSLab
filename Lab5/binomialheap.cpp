#include <iostream>
#include <climits>

using namespace std;

// Structure for a Binomial Heap Node
struct BinomialNode {
    int key;
    int degree;
    BinomialNode *parent, *child, *sibling;

    BinomialNode(int val) {
        key = val;
        degree = 0;
        parent = child = sibling = nullptr;
    }
};

// Function to merge two Binomial Trees
BinomialNode* mergeBinomialTrees(BinomialNode* b1, BinomialNode* b2) {
    if (b1->key > b2->key) 
        swap(b1, b2);
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

// Function to merge two Binomial Heaps
BinomialNode* mergeHeaps(BinomialNode* h1, BinomialNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    BinomialNode* head = nullptr;
    BinomialNode* tail = nullptr;
    BinomialNode* p1 = h1;
    BinomialNode* p2 = h2;

    while (p1 && p2) {
        BinomialNode* minNode = nullptr;
        if (p1->degree <= p2->degree) {
            minNode = p1;
            p1 = p1->sibling;
        } else {
            minNode = p2;
            p2 = p2->sibling;
        }

        if (!head) {
            head = minNode;
            tail = minNode;
        } else {
            tail->sibling = minNode;
            tail = minNode;
        }
    }

    tail->sibling = (p1) ? p1 : p2;
    return head;
}

// Function to unite two Binomial Heaps
BinomialNode* uniteHeaps(BinomialNode* h1, BinomialNode* h2) {
    BinomialNode* mergedHeap = mergeHeaps(h1, h2);
    if (!mergedHeap) return nullptr;

    BinomialNode* prev = nullptr;
    BinomialNode* curr = mergedHeap;
    BinomialNode* next = curr->sibling;

    while (next) {
        if ((curr->degree != next->degree) || 
           (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                mergeBinomialTrees(curr, next);
            } else {
                if (!prev) 
                    mergedHeap = next;
                else
                    prev->sibling = next;
                mergeBinomialTrees(next, curr);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return mergedHeap;
}

// Insert a node in Binomial Heap
BinomialNode* insert(BinomialNode* heap, int key) {
    BinomialNode* newNode = new BinomialNode(key);
    return uniteHeaps(heap, newNode);
}

// Find the minimum key in Binomial Heap
BinomialNode* findMin(BinomialNode* heap) {
    if (!heap) return nullptr;

    BinomialNode* minNode = heap;
    BinomialNode* temp = heap;

    while (temp) {
        if (temp->key < minNode->key)
            minNode = temp;
        temp = temp->sibling;
    }
    return minNode;
}

// Extract minimum key from Binomial Heap
BinomialNode* extractMin(BinomialNode*& heap) {
    if (!heap) return nullptr;

    BinomialNode* minNode = findMin(heap);
    if (!minNode) return nullptr;

    BinomialNode* prev = nullptr;
    BinomialNode* temp = heap;
    while (temp != minNode) {
        prev = temp;
        temp = temp->sibling;
    }

    if (prev) 
        prev->sibling = temp->sibling;
    else 
        heap = temp->sibling;

    BinomialNode* childHeap = nullptr;
    BinomialNode* child = minNode->child;
    while (child) {
        BinomialNode* next = child->sibling;
        child->sibling = childHeap;
        child->parent = nullptr;
        childHeap = child;
        child = next;
    }

    heap = uniteHeaps(heap, childHeap);
    return minNode;
}

// Decrease key operation
void decreaseKey(BinomialNode* node, int newKey) {
    if (!node || newKey > node->key) {
        cout << "Invalid operation\n";
        return;
    }
    node->key = newKey;
    BinomialNode* curr = node;
    BinomialNode* parent = node->parent;

    while (parent && curr->key < parent->key) {
        swap(curr->key, parent->key);
        curr = parent;
        parent = curr->parent;
    }
}

// Delete key
BinomialNode* deleteKey(BinomialNode* heap, int key) {
    BinomialNode* minNode = findMin(heap);
    if (!minNode) return heap;

    decreaseKey(minNode, INT_MIN);
    extractMin(heap);
    return heap;
}

void printTree(BinomialNode* node) {
    if (!node) return;
    cout << node->key << " ";
    printTree(node->child);  // Recursively print child nodes
    printTree(node->sibling); // Move to sibling node
}

void displayHeap(BinomialNode* heap) {
    if (!heap) {
        cout << "Heap is empty\n";
        return;
    }

    cout << "Binomial Heap:\n";
    BinomialNode* temp = heap;
    
    while (temp) {
        cout << "B" << temp->degree << " ( ";
        printTree(temp);
        cout << ")\n";
        temp = temp->sibling; // Move to the next binomial tree in the heap
    }
}


// Main function with user-driven menu
int main() {
    BinomialNode* heap = nullptr;
    int choice, key;

    do {
        cout << "\nBinomial Heap Operations:\n";
        cout << "1. Insert Key\n";
        cout << "2. Find Minimum Key\n";
        cout << "3. Extract Minimum Key\n";
        cout << "4. Decrease Key\n";
        cout << "5. Delete Key\n";
        cout << "6. Display Heap\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                heap = insert(heap, key);
                break;
            case 2:
                if (BinomialNode* minNode = findMin(heap))
                    cout << "Minimum Key: " << minNode->key << endl;
                else
                    cout << "Heap is empty\n";
                break;
            case 3:
                BinomialNode* minNode;
                if (minNode = extractMin(heap))
                    cout << "Extracted Minimum Key: " << minNode->key << endl;
                else
                    cout << "Heap is empty\n";
                delete minNode;
                break;
            case 4:
                cout << "Enter key to decrease: ";
                cin >> key;
                decreaseKey(findMin(heap), key);
                break;
            case 5:
                cout << "Enter key to delete: ";
                cin >> key;
                heap = deleteKey(heap, key);
                break;
            case 6:
                displayHeap(heap);
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
