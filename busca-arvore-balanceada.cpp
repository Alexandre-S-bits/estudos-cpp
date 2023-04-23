#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    return node->height;
}

Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

Node* rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node* rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        root = new Node;
        root->value = value;
        root->left = nullptr;
        root->right = nullptr;
        root->height = 0;
    } else if (value < root->value) {
        root->left = insert(root->left, value);
        if (getHeight(root->left) - getHeight(root->right) == 2) {
            if (value < root->left->value) {
                root = rotateRight(root);
            } else {
                root = rotateLeftRight(root);
            }
        }
    } else if (value > root->value) {
        root->right = insert(root->right, value);
        if (getHeight(root->right) - getHeight(root->left) == 2) {
            if (value > root->right->value) {
                root = rotateLeft(root);
            } else {
                root = rotateRightLeft(root);
            }
        }
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    return root;
}

Node* search(Node* root, int value) {
    if (root == nullptr || root->value == value) {
        return root;
    }
    if (root->value < value) {
        return search(root->right, value);
    } else {
        return search(root->left, value);
    }
}

void printInOrder(Node* root) {
    if (root == nullptr) {
        return;
    }
    printInOrder(root->left);
    cout << root->value << " ";
    printInOrder(root->right);
}

int main() {
    Node* root = nullptr;

    root = insert(root, 50);
    root = insert(root, 20);
    root = insert(root, 70);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "In-order traversal: ";
    printInOrder(root);
    cout << endl;

    int value = 60;
    Node* result = search(root, value);
