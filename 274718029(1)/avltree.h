#pragma once
#include <string>
#include <iostream>
using namespace std;
struct AVLTree {
    struct TreeNode {
        //id, names, height, left, right, factor = difference ( - )
        string ID;
        string name;
        int height;
        TreeNode* left;
        TreeNode* right;
        int balanceFactor;
        TreeNode(string userName, string userID)
                : name(userName), ID(userID), left(nullptr), right(nullptr), height(0), balanceFactor(0) {}
    };
    TreeNode* root;
    int size;
    AVLTree() : root(nullptr), size(0) {}
    int getHeight(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* rotateLR(TreeNode* node);
    TreeNode* rotateRL(TreeNode* node);
    TreeNode* balanceNode(TreeNode* node);
    TreeNode* insertHelper(TreeNode* root, string name, string ID);
    TreeNode* removeHelper(TreeNode* root, string ID);
    TreeNode* searchHelper(TreeNode* node, string name_or_ID, bool& found, bool searchByID);
    void printInorderHelper(TreeNode* node, bool& isFirstNode);
    void printPreorderHelper(TreeNode* node, bool& isFirstNode);
    void printPostorderHelper(TreeNode* node, bool& isFirstNode);
    void removeInorderHelper(int n, int& count, TreeNode* node);
    void insert(string name, string ID);
    void remove(string ID);
    void search(string name_or_ID);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int n);
};
int AVLTree::getHeight(TreeNode* node) {
    return node ? node->height : -1;
}
AVLTree::TreeNode* AVLTree::rotateLeft(TreeNode* node) {
    TreeNode* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;
    return newParent;
}
AVLTree::TreeNode* AVLTree::rotateRight(TreeNode* node) {
    TreeNode* newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;
    return newParent;
}
AVLTree::TreeNode* AVLTree::rotateLR(TreeNode* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}
AVLTree::TreeNode* AVLTree::rotateRL(TreeNode* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}
AVLTree::TreeNode* AVLTree::balanceNode(TreeNode* node) {
    if (node->balanceFactor == -2) {
        if (getHeight(node->right->left) > getHeight(node->right->right)) {
            node = rotateRL(node);
        } else {
            node = rotateLeft(node);
        }
    } else if (node->balanceFactor == 2) {
        if (getHeight(node->left->right) > getHeight(node->left->left)) {
            node = rotateLR(node);
        } else {
            node = rotateRight(node);
        }
    }
    node->balanceFactor = getHeight(node->left) - getHeight(node->right);
    return node;
}
void AVLTree::insert(string name, string ID) {
    if (!root) {
        root = new TreeNode(name, ID);
        size++;
        cout << "successful\n";
    } else {
        root = insertHelper(root, name, ID);
    }
}
AVLTree::TreeNode* AVLTree::insertHelper(TreeNode* node, string name, string ID) {
    if (!node) {
        cout << "successful\n";
        size++;
        return new TreeNode(name, ID);
    }
    if (ID == node->ID) {
        cout << "unsuccessful\n";
    } else if (ID < node->ID) {
        node->left = insertHelper(node->left, name, ID);
    } else {
        node->right = insertHelper(node->right, name, ID);
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    node->balanceFactor = getHeight(node->left) - getHeight(node->right);
    return balanceNode(node);
}
void AVLTree::remove(string ID) {
    root = removeHelper(root, ID);
}
AVLTree::TreeNode* AVLTree::removeHelper(TreeNode* node, string ID) {
    if (!node) {
        cout << "unsuccessful\n";
        return nullptr;
    }
    if (ID < node->ID) {
        node->left = removeHelper(node->left, ID);
    } else if (ID > node->ID) {
        node->right = removeHelper(node->right, ID);
    } else {
        if (!node->left && !node->right) {
            delete node;
            size--;
            cout << "successful\n";
            return nullptr;
        } else if (node->left && node->right) {
            TreeNode* successor = node->right;
            while (successor->left) {
                successor = successor->left;
            }
            node->ID = successor->ID;
            node->name = successor->name;
            node->right = removeHelper(node->right, successor->ID);
        } else {
            TreeNode* temp = node->left ? node->left : node->right;
            delete node;
            size--;
            cout << "successful\n";
            return temp;
        }
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    node->balanceFactor = getHeight(node->left) - getHeight(node->right);
    return balanceNode(node);
}
bool isValidID(const string& ID) {
    if (ID.length() != 8) return false;
    for (char c : ID) {
        if (!isdigit(c)) return false;
    }
    return true;
}
void AVLTree::search(string name_or_ID) {
    bool found = false;
    if (isValidID(name_or_ID)) {
        searchHelper(root, name_or_ID, found, true);
    } else {
        searchHelper(root, name_or_ID, found, false);
    }
    if (!found) {
        cout << "unsuccessful\n";
    }
}
AVLTree::TreeNode* AVLTree::searchHelper(TreeNode* node, string name_or_ID, bool& found, bool searchByID) {
    if (!node) return nullptr;
    if (searchByID) {
        if (node->ID == name_or_ID) {
            cout << node->name << endl;
            found = true;
            return node;
        } else if (name_or_ID < node->ID) {
            return searchHelper(node->left, name_or_ID, found, searchByID);
        } else {
            return searchHelper(node->right, name_or_ID, found, searchByID);
        }
    } else {
        if (node->name == name_or_ID) {
            cout << node->ID << endl;
            found = true;
        }
        searchHelper(node->left, name_or_ID, found, searchByID);
        searchHelper(node->right, name_or_ID, found, searchByID);
    }
    return nullptr;
}
bool verName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && !isdigit(c) && c != ' ')
            return false;
    }
    return true;
}
bool verID(string ID) {
    int temp;
    temp = stoi(ID);
    return (ID.length() == 8);

}
void AVLTree::printInorder() {
    bool isFirstNode = true;
    printInorderHelper(root, isFirstNode);
    cout << "\n";
}
void AVLTree::printInorderHelper(TreeNode* node, bool& isFirstNode) {
    if (!node) return;
    printInorderHelper(node->left, isFirstNode);
    if (isFirstNode) {
        cout << node->name;
        isFirstNode = false;
    } else {
        cout << ", " << node->name;
    }
    printInorderHelper(node->right, isFirstNode);
}
void AVLTree::printPreorder() {
    bool isFirstNode = true;
    printPreorderHelper(root, isFirstNode);
    cout << "\n";
}
void AVLTree::printPreorderHelper(TreeNode* node, bool& isFirstNode) {
    if (!node) return;
    if (isFirstNode) {
        cout << node->name;
        isFirstNode = false;
    } else {
        cout << ", " << node->name;
    }
    printPreorderHelper(node->left, isFirstNode);
    printPreorderHelper(node->right, isFirstNode);
}
void AVLTree::printPostorder() {
    bool isFirstNode = true;
    printPostorderHelper(root, isFirstNode);
    cout << "\n";
}
void AVLTree::printPostorderHelper(TreeNode* node, bool& isFirstNode) {
    if (!node) return;
    printPostorderHelper(node->left, isFirstNode);
    printPostorderHelper(node->right, isFirstNode);
    if (isFirstNode) {
        cout << node->name;
        isFirstNode = false;
    } else {
        cout << ", " << node->name;
    }
}
void AVLTree::printLevelCount() {
    if (!root) {
        cout << "0" << endl;
    } else {
        cout << root->height + 1 << endl;
    }
}
void AVLTree::removeInorder(int n) {
    if (n >= size) {
        cout << "unsuccessful\n";
        return;
    }
    int count = -1;
    removeInorderHelper(n, count, root);
}
void AVLTree::removeInorderHelper(int n, int& count, TreeNode* node) {
    if (!node) return;
    removeInorderHelper(n, count, node->left);
    count++;
    if (count == n) {
        remove(node->ID);
        return;
    }
    removeInorderHelper(n, count, node->right);
}