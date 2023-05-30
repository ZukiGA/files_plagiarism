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
};

int main() {
    BinaryTree tree;

    tree.insert(4);
    tree.insert(6);

    cout << "In-order Traversal: ";
    tree.traverseInOrder();

    cout << "Search for 4: " << (tree.search(4) ? "Found" : "Not found") << endl;

    return 0;
}