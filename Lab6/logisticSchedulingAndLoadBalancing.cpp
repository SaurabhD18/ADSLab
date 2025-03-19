#include <iostream>
#include <climits>
using namespace std;

// Binomial Heap Node
struct Delivery {
    int id;         // Delivery ID
    int priority;   // Priority based on urgency & distance
    int degree;     
    Delivery *parent, *child, *sibling;

    Delivery(int id, int priority) {
        this->id = id;
        this->priority = priority;
        degree = 0;
        parent = child = sibling = nullptr;
    }
};

// Merge two Binomial Trees
Delivery* mergeBinomialTrees(Delivery* b1, Delivery* b2) {
    if (b1->priority > b2->priority)
        swap(b1, b2);
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

// Merge two Binomial Heaps
Delivery* mergeHeaps(Delivery* h1, Delivery* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    Delivery* head = nullptr, *tail = nullptr, *p1 = h1, *p2 = h2;
    
    while (p1 && p2) {
        Delivery* minNode = (p1->degree <= p2->degree) ? p1 : p2;
        if (minNode == p1) p1 = p1->sibling;
        else p2 = p2->sibling;

        if (!head) head = tail = minNode;
        else tail = tail->sibling = minNode;
    }
    tail->sibling = (p1) ? p1 : p2;
    return head;
}

// Unite two Binomial Heaps
Delivery* uniteHeaps(Delivery* h1, Delivery* h2) {
    Delivery* mergedHeap = mergeHeaps(h1, h2);
    if (!mergedHeap) return nullptr;

    Delivery* prev = nullptr, *curr = mergedHeap, *next = curr->sibling;
    
    while (next) {
        if ((curr->degree != next->degree) || 
           (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->priority <= next->priority) {
                curr->sibling = next->sibling;
                mergeBinomialTrees(curr, next);
            } else {
                if (!prev) mergedHeap = next;
                else prev->sibling = next;
                mergeBinomialTrees(next, curr);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return mergedHeap;
}

// Insert a delivery request
Delivery* insert(Delivery* heap, int id, int priority) {
    Delivery* newNode = new Delivery(id, priority);
    return uniteHeaps(heap, newNode);
}

// Find the highest priority delivery
Delivery* findMin(Delivery* heap) {
    if (!heap) return nullptr;
    Delivery* minNode = heap;
    for (Delivery* temp = heap; temp; temp = temp->sibling)
        if (temp->priority < minNode->priority)
            minNode = temp;
    return minNode;
}

// Extract the highest priority delivery
Delivery* extractMin(Delivery*& heap) {
    if (!heap) return nullptr;

    Delivery* minNode = findMin(heap);
    if (!minNode) return nullptr;

    Delivery* prev = nullptr, *temp = heap;
    while (temp != minNode) {
        prev = temp;
        temp = temp->sibling;
    }

    if (prev) prev->sibling = temp->sibling;
    else heap = temp->sibling;

    Delivery* childHeap = nullptr, *child = minNode->child;
    while (child) {
        Delivery* next = child->sibling;
        child->sibling = childHeap;
        child->parent = nullptr;
        childHeap = child;
        child = next;
    }

    heap = uniteHeaps(heap, childHeap);
    return minNode;
}

// Decrease Priority
void decreasePriority(Delivery* node, int newPriority) {
    if (!node || newPriority > node->priority) {
        cout << "Invalid operation\n";
        return;
    }
    node->priority = newPriority;
    Delivery* curr = node, *parent = node->parent;

    while (parent && curr->priority < parent->priority) {
        swap(curr->priority, parent->priority);
        swap(curr->id, parent->id);
        curr = parent;
        parent = curr->parent;
    }
}

// Delete a delivery request
Delivery* deleteDelivery(Delivery* heap, int id) {
    Delivery* minNode = findMin(heap);
    if (!minNode) return heap;

    decreasePriority(minNode, INT_MIN);
    extractMin(heap);
    return heap;
}

// Display Heap
void printTree(Delivery* node) {
    if (!node) return;
    cout << "[ID: " << node->id << ", P: " << node->priority << "] ";
    printTree(node->child);
    printTree(node->sibling);
}

void displayHeap(Delivery* heap) {
    if (!heap) {
        cout << "Heap is empty\n";
        return;
    }
    cout << "Delivery Schedule:\n";
    for (Delivery* temp = heap; temp; temp = temp->sibling) {
        cout << "B" << temp->degree << " ( ";
        printTree(temp);
        cout << ")\n";
    }
}

// Main Function
int main() {
    Delivery* heap = nullptr;
    int choice, id, priority;

    do {
        cout << "\nLogistics Scheduling System:\n";
        cout << "1. Add Delivery Request\n";
        cout << "2. View Next Delivery\n";
        cout << "3. Dispatch Next Delivery\n";
        cout << "4. Update Delivery Priority\n";
        cout << "5. Remove a Delivery\n";
        cout << "6. Display Schedule\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Delivery ID and Priority: ";
                cin >> id >> priority;
                heap = insert(heap, id, priority);
                break;
            case 2:
                if (Delivery* minNode = findMin(heap))
                    cout << "Next Delivery: ID " << minNode->id << " (Priority: " << minNode->priority << ")\n";
                else
                    cout << "No pending deliveries\n";
                break;
            case 3:
                Delivery* minNode;
                if (minNode = extractMin(heap))
                    cout << "Dispatched Delivery ID: " << minNode->id << endl;
                else
                    cout << "No pending deliveries\n";
                delete minNode;
                break;
            case 4:
                cout << "Enter Delivery ID and New Priority: ";
                cin >> id >> priority;
                decreasePriority(findMin(heap), priority);
                break;
            case 5:
                cout << "Enter Delivery ID to Remove: ";
                cin >> id;
                heap = deleteDelivery(heap, id);
                break;
            case 6:
                displayHeap(heap);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
