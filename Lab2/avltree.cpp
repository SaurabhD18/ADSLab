#include <iostream>
using namespace std;

class AVLNode { // AVL Tree Node
public:
    int key, height;
    AVLNode *left, *right;
    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree { // AVL Tree
public:
    int getHeight(AVLNode* node) { // Get Height of Node
        return node ? node->height : 0;
    }

    int getBalanceFactor(AVLNode* node) { // Get Balance Factor of Node
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* z) { // Right Rotate
        AVLNode* y = z->left;
        AVLNode* T3 = y->right;
        y->right = z;
        z->left = T3;
        z->height = max(getHeight(z->left), getHeight(z->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode* leftRotate(AVLNode* z) { // Left Rotate
        AVLNode* y = z->right;
        AVLNode* T2 = y->left;
        y->left = z;
        z->right = T2;
        z->height = max(getHeight(z->left), getHeight(z->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode* root, int key) { // Insert Node in AVL Tree (Recursive)
        if (!root) return new AVLNode(key);
        if (key < root->key) root->left = insert(root->left, key);
        else root->right = insert(root->right, key);
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        int balance = getBalanceFactor(root);
        if (balance > 1 && key < root->left->key) return rightRotate(root);
        if (balance < -1 && key > root->right->key) return leftRotate(root);
        if (balance > 1 && key > root->left->key) { // Left Right Case (Left Rotate Left Child, Right Rotate Root)
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && key < root->right->key) { // Right Left Case (Right Rotate Right Child, Left Rotate Root)
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    AVLNode* minValueNode(AVLNode* node) { // Get Node with Minimum Value
        while (node->left) node = node->left;
        return node;
    }

    AVLNode* deleteNode(AVLNode* root, int key) { // Delete Node from AVL Tree (Recursive)
        if (!root) return root;
        if (key < root->key) root->left = deleteNode(root->left, key);
        else if (key > root->key) root->right = deleteNode(root->right, key);
        else {
            if (!root->left) return root->right;
            if (!root->right) return root->left;
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        int balance = getBalanceFactor(root);
        if (balance > 1 && getBalanceFactor(root->left) >= 0) return rightRotate(root); // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {  // Left Right Case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalanceFactor(root->right) <= 0) return leftRotate(root); // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) > 0) { // Right Left Case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    void inorderTraversal(AVLNode* root) { // Inorder Traversal
        if (root) {
            inorderTraversal(root->left);
            cout << root->key << " ";
            inorderTraversal(root->right);
        }
    }
};

int main() {
    AVLTree tree;
    AVLNode* root = nullptr;
    int insert_values[] = {10, 20, 30, 40, 50, 25};
    int delete_value = 30;
    for (int value : insert_values) root = tree.insert(root, value);
    root = tree.deleteNode(root, delete_value);
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(root);
    cout << "\nHeight of AVL Tree: " << tree.getHeight(root);
    cout << "\nBalance Factor of Root (" << root->key << "): " << tree.getBalanceFactor(root) << endl;
    return 0;
}