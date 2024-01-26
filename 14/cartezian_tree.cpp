#include <iostream>
#include <cstdlib>

using namespace std;

class TreapNode {
public:
    int value;
    int priority;
    int size;
    int subtreeSum;  

    TreapNode* left;
    TreapNode* right;

    TreapNode(int val) {
        value = val;
        priority = rand();
        size = 1;
        subtreeSum = val;  
        left = nullptr;
        right = nullptr;
    }
};

class Treap {
public:
    void insert(int val, int pos) {
        split(root, pos, left, right);
        root = merge(merge(left, new TreapNode(val)), right);
    }

    void erase(int pos) {
        split(root, pos, left, right);
        split(right, 1, eraseNode, right);
        delete eraseNode;
        root = merge(left, right);
    }

    void erase(int pos, int count) {
        split(root, pos, left, right);
        split(right, count, eraseNode, right);
        deleteSubtree(eraseNode);
        root = merge(left, right);
    }

    int sum(int from, int to) {
        split(root, from - 1, left, right);
        split(right, to - from + 1, middle, right);
        int result = getSum(middle);
        root = merge(merge(left, middle), right);
        return result;
    }

private:
    TreapNode* root = nullptr;
    TreapNode* left = nullptr;
    TreapNode* right = nullptr;
    TreapNode* eraseNode = nullptr;
    TreapNode* middle = nullptr;

    void split(TreapNode* node, int pos, TreapNode*& left, TreapNode*& right) {
        if (node == nullptr) {
            left = right = nullptr;
        }
        else if (pos <= getSize(node->left)) {
            split(node->left, pos, left, node->left);
            right = node;
        }
        else {
            split(node->right, pos - 1 - getSize(node->left), node->right, right);
            left = node;
        }
        updateSize(node);
    }

    TreapNode* merge(TreapNode* left, TreapNode* right) {
        if (left == nullptr || right == nullptr) {
            if (left == nullptr) return right;
            else return left;
        }
        else if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            updateSize(left);
            updateSubtreeSum(left);  
            return left;
        }
        else {
            right->left = merge(left, right->left);
            updateSize(right);
            updateSubtreeSum(right);  
            return right;
        }
    }

    void deleteSubtree(TreapNode* node) {
        if (node != nullptr) {
            deleteSubtree(node->left);
            deleteSubtree(node->right);
            delete node;
        }
    }

    int getSum(TreapNode* node) {
        if (node == nullptr) return 0;
        return node->subtreeSum;
    }

    int getSize(TreapNode* node) {
        if (node == nullptr) return 0;
        return node->size;
    }

    void updateSize(TreapNode* node) {
        if (node != nullptr) {
            node->size = getSize(node->left) + getSize(node->right) + 1;
        }
    }

    void updateSubtreeSum(TreapNode* node) {
        if (node != nullptr) {
            node->subtreeSum = node->value + getSum(node->left) + getSum(node->right);
        }
    }

    int getSubtreeSum(TreapNode* node) {
        if (node == nullptr) return 0;
        return node->subtreeSum;
    }
};

int main() {
    Treap treap;

    int checkSum = 0;

    //------ TESTS ------
    for (int i = 0; i < 100000; i++) {
        int value = rand();
        treap.insert(value, 0);
        checkSum += value;
    }

    cout << "sum of treap:\t " << treap.sum(0, 99999) << endl;
    cout << "checkSum: \t" << checkSum << endl;

    for (int i = 0; i < 100000; i++) {
        treap.erase(0);
    }

    for (int i = 0; i < 5; i++) {
        treap.insert(1, 0);
    }

    cout << "sum of [1:4]:\t " << treap.sum(1, 4) << endl;
    cout << "expected sum:\t " << 4 << endl;

    return 0;
}
