#include <iostream>
using namespace std;

class TreeNode {
public:
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree {
private:
    TreeNode* root;

    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    TreeNode* rotateRight(TreeNode* node) {
        TreeNode* newRoot = node->left;
        TreeNode* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    TreeNode* rotateLeft(TreeNode* node) {
        TreeNode* newRoot = node->right;
        TreeNode* temp = newRoot->left;

        newRoot->left = node;
        node->right = temp;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    TreeNode* insertNode(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        } else {
            return node;  // Duplicates not allowed
        }

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* findMinNode(TreeNode* node) {
        if (node->left == nullptr) {
            return node;
        }
        return findMinNode(node->left);
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

        if (node == nullptr) {
            return nullptr;
        }

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        // Left Right Case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Right Left Case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
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

public:
    AVLTree() {
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
    AVLTree tree;

    tree.insert(9);
    tree.insert(5);
    tree.insert(10);
    tree.insert(0);
    tree.insert(6);
    tree.insert(11);
    tree.insert(-1);
    tree.insert(1);
    tree.insert(2);

    cout << "AVL Tree:" << endl;
    tree.print();

    cout << "In-order Traversal: ";
    tree.traverseInOrder();

    cout << "Search for 6: " << (tree.search(6) ? "Found" : "Not found") << endl;
    cout << "Search for 8: " << (tree.search(8) ? "Found" : "Not found") << endl;

    tree.remove(10);

    cout << "AVL Tree after deletion:" << endl;
    tree.print();

    return 0;
}
