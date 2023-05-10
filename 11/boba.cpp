#include <iostream>
#include <map>

using namespace std;

// Структура для хранения информации о цели
struct Target {
    int reward;  // награда за голову
    int rank;    // ранг цели
};

// AVL-дерево для хранения целей
class TargetTree {
private:
    // Структура узла дерева
    struct Node {
        int key;           // ключ (идентификатор цели)
        Target value;      // информация о цели
        int height;        // высота поддерева
        Node* left;        // левое поддерево
        Node* right;       // правое поддерево
        Node(int k, Target v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
    };
    Node* root;           // корень дерева

    // Вспомогательные функции для поддержания баланса дерева
    int height(Node* node) {
        return node ? node->height : 0;
    }
    int balanceFactor(Node* node) {
        return height(node->right) - height(node->left);
    }
    void fixHeight(Node* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
    Node* rotateRight(Node* node) {
        Node* q = node->left;
        node->left = q->right;
        q->right = node;
        fixHeight(node);
        fixHeight(q);
        return q;
    }
    Node* rotateLeft(Node* node) {
        Node* p = node->right;
        node->right = p->left;
        p->left = node;
        fixHeight(node);
        fixHeight(p);
        return p;
    }
    Node* balance(Node* node) {
        fixHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        return node;
    }

public:
    TargetTree() : root(nullptr) {}

    // Поиск цели по ключу
    bool find(int key, Target& target) {
        Node* node = root;
        while (node) {
            if (node->key == key) {
                target = node->value;
                return true;
            }
            if (node->key < key)
                node = node->right;
            else
                node = node->left;
        }
        return false;
    }

    // Вставка новой цели
    void insert(int key, Target target) {
        Node* node = root;
        Node* parent = nullptr;
        while (node) {
            parent = node;
            if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        Node* newNode = new Node(key, target);
        if (!parent) {
            root = newNode;
            return;
        } if (key < parent->key)
            parent->left = newNode;
        else
            parent->right = newNode;
        root = balance(root);
    }

    // Удаление цели по ключу
    void remove(int key) {
        Node* node = root;
        Node* parent = nullptr;
        while (node) {
            if (node->key == key)
                break;
            parent = node;
            if (node->key < key)
                node = node->right;
            else
                node = node->left;
        }
        if (!node)
            return;
        if (!node->left && !node->right) {
            if (!parent) {
                root = nullptr;
                delete node;
                return;
            }
            if (parent->left == node)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete node;
        }
        else if (!node->left || !node->right) {
            Node* child = node->left ? node->left : node->right;
            if (!parent) {
                root = child;
                delete node;
                return;
            }
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
            delete node;
        }
        else {
            Node* minNode = node->right;
            while (minNode->left)
                minNode = minNode->left;
            node->key = minNode->key;
            node->value = minNode->value;
            remove(minNode->key);
        }
        root = balance(root);
    }

    // Вывод всех целей в отсортированном порядке по ключу
    void printInOrder() {
        printInOrder(root);
    }
    void printInOrder(Node* node) {
        if (!node)
            return;
        printInOrder(node->left);
        cout << "Key: " << node->key << ", Reward: " << node->value.reward << ", Rank: " << node->value.rank << endl;
        printInOrder(node->right);
    }
};

    int main() {
        TargetTree tree;
        tree.insert(3, { 100, 2 });
        tree.insert(1, { 50, 1 });
        tree.insert(2, { 75, 2 });
        tree.insert(5, { 200, 3 });
        tree.insert(4, { 150, 3 });
        Target target;
        if (tree.find(3, target))
            cout << "Reward for target 3: " << target.reward << endl;
        else
            cout << "Target 3 not found" << endl;

        tree.remove(2);

        cout << "Targets in order:" << endl;
        tree.printInOrder();

        return 0;
    }
