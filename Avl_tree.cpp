#include <iostream>

// Structure for AVL tree node
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new AVL tree node
Node* createNode(int key) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

// Function to perform a right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Function to perform a left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Function to insert a key into the AVL tree
Node* insertNode(Node* root, int key) {
    // Perform standard BST insertion
    if (root == nullptr)
        return createNode(key);

    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    else
        return root; // Duplicate keys are not allowed in AVL tree

    // Update the height of the ancestor node
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    // Check the balance factor and perform necessary rotations
    int balanceFactor = getBalanceFactor(root);

    // Left Left Case
    if (balanceFactor > 1 && key < root->left->key)
        return rotateRight(root);

    // Right Right Case
    if (balanceFactor < -1 && key > root->right->key)
        return rotateLeft(root);

    // Left Right Case
    if (balanceFactor > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (balanceFactor < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to print the AVL tree in inorder traversal
void inorderTraversal(Node* root) {
    if (root == nullptr)
        return;

    inorderTraversal(root->left);
    std::cout << root->key << " ";
    inorderTraversal(root->right);
}

// Main function
int main() {
    Node* root = nullptr;

    // Insert nodes into the AVL tree
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    // Print the AVL tree
    std::cout << "Inorder traversal of AVL tree: ";
    inorderTraversal(root);

    return 0;
}
