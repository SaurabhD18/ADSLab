#include <iostream>
using namespace std;

struct treapNode {
    int key, priority;
    treapNode *left, *right;
};

treapNode* newNode(int key, int priority) {
    treapNode* temp = new treapNode;
    temp->key = key;
    temp->priority = priority;
    temp->left = temp->right = nullptr;
    return temp;
}

treapNode* rightRotate(treapNode* y) {
    treapNode* x = y->left;
    treapNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

treapNode* leftRotate(treapNode* x) {
    treapNode* y = x->right;
    treapNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

treapNode* insert(treapNode* root, int key, int priority) {
    if (!root) return newNode(key, priority);

    if (key <= root->key) {
        root->left = insert(root->left, key, priority);
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    } else {
        root->right = insert(root->right, key, priority);
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}

treapNode* deleteNode(treapNode* root, int key) {
    if (!root) return root;

    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else if (root->left == nullptr) {
        treapNode* temp = root->right;
        delete root;
        return temp;
    } else if (root->right == nullptr) {
        treapNode* temp = root->left;
        delete root;
        return temp;
    } else if (root->left->priority < root->right->priority) {
        root = leftRotate(root);
        root->left = deleteNode(root->left, key);
    } else {
        root = rightRotate(root);
        root->right = deleteNode(root->right, key);
    }
    return root;
}

treapNode* findMaxPriority(treapNode* root) {
    if (!root) return nullptr;
    if (root->right) return findMaxPriority(root->right);
    return root;
}

void inorder(treapNode* root) {
    if (root) {
        inorder(root->left);
        cout << "Task ID: " << root->key << " Priority: " << root->priority << endl;
        inorder(root->right);
    }
}

int main() {
    treapNode* root = nullptr;
    int choice, key, priority;
    do {
        cout << "\nTask Scheduler Menu:\n";
        cout << "1. Insert Task\n2. Delete Task\n3. Find Highest Priority Task\n4. Display Tasks (Inorder)\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> key;
                cout << "Enter Priority: ";
                cin >> priority;
                root = insert(root, key, priority);
                break;
            case 2:
                cout << "Enter Task ID to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3: {
                treapNode* maxPriority = findMaxPriority(root);
                if (maxPriority)
                    cout << "Highest Priority Task: Task ID: " << maxPriority->key << " Priority: " << maxPriority->priority << endl;
                else
                    cout << "No tasks available.\n";
                break;
            }
            case 4:
                cout << "\nTask List (Inorder Traversal):\n";
                inorder(root);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    return 0;
}
