#include <iostream>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    TreeNode* root;

    TreeNode* insertNode(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else {
            node->right = insertNode(node->right, value);
        }

        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                TreeNode* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node;
                node = node->left;
                delete temp;
            } else {
                TreeNode* temp = findMinNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

         return node;
    }

    void inOrderTraversal(TreeNode* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    void printTree(TreeNode* node, int indent = 0) {
        if (node == nullptr) {
            return;
        }

        printTree(node->right, indent + 4);

        cout << string(indent, ' ') << node->data << endl;

        printTree(node->left, indent + 4);
    }

    TreeNode* findMinNode(TreeNode* node) {
        if (node->left == nullptr) {
            return node;
        }
        return findMinNode(node->left);
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void traverseInOrder() {
        inOrderTraversal(root);
        cout << endl;
    }

    void print() {
        printTree(root);
    }

    bool search(int value) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return true;
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }
};

int main() {
    BinaryTree tree;

    tree.insert(5);
    tree.insert(2);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "Binary Tree:" << endl;
    tree.print();

    cout << "In-order Traversal: ";
    tree.traverseInOrder();

    cout << "Search for 4: " << (tree.search(4) ? "Found" : "Not found") << endl;
    cout << "Search for 9: " << (tree.search(9) ? "Found" : "Not found") << endl;

    tree.remove(2);

    cout << "Binary Tree after deletion:" << endl;
    tree.print();

    return 0;
}



