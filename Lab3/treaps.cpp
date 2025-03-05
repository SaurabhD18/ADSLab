// Q) Use Treap to implement a priority-based task scheduler where each task has a unique ID
// (key) and a priority. Higher-priority tasks should be completed first while maintaining the
// properƟes of a Binary Search Tree (BST).
// Tasks:
// 1. Insert tasks into Treap – Each task has a unique task ID (key) and an assigned priority.
// 2. Delete completed tasks – Remove a task once it's completed.
// 3. Find the highest-priority task – Retrieve the task with the highest priority efficiently. \

#include <iostream>

struct treapNode {
    int key, priority;
    treapNode *left, *right;
};

using namespace std;


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


treapNode* search(treapNode* root, int key) {
    if (!root || root->key == key) return root;

    if (root->key < key) return search(root->right, key);

    return search(root->left, key);
}


treapNode* deleteNode(treapNode* root, int key) {
    if (!root) return root;

    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else if (root->left == nullptr) {
        treapNode* temp = root->right;
        delete root;
        root = temp;
    } else if (root->right == nullptr) {
        treapNode* temp = root->left;
        delete root;
        root = temp;
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
    root = insert(root, 4, 10);
    root = insert(root, 2, 5);
    root = insert(root, 6, 15);
    root = insert(root, 1, 20);
    root = insert(root, 3, 7);
    root = insert(root, 5, 3);
    root = insert(root, 7, 8);

    cout << "Inorder traversal of the given tree \n";
    inorder(root);

    cout << "\nDelete task 4\n";
    root = deleteNode(root, 4);
    cout << "Inorder traversal of the modified tree \n";
    inorder(root);

    treapNode* maxPriority = findMaxPriority(root);
    cout << "\nTask with highest priority: Task ID: " << maxPriority->key << " Priority: " << maxPriority->priority << endl;

    return 0;
}