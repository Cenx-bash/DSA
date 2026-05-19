#include <iostream>
using namespace std;

// Definition of a BST Node
struct Node {
    int data;
    Node *left, *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Function to insert a new node into the BST
Node* insert(Node* root, int val) {
    if (root == nullptr) return new Node(val);

    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

// Function to search for a value in the BST
bool search(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;

    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

// In-order Traversal (Prints nodes in ascending order)
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    
    // Inserting values
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);

    cout << "In-order Traversal: ";
    inorder(root); // Output: 20 30 40 50 70
    cout << endl;

    // Searching for a value
    int key = 40;
    if (search(root, key)) {
        cout << key << " found in the tree." << endl;
    } else {
        cout << key << " not found." << endl;
    }

    return 0;
}

