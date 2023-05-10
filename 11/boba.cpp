#include <iostream>
#include <queue>
#include <string>
#include <sstream>

#define null NULL

using namespace std;

template <typename Key, typename Value>
class AVLTree {
public:
    struct TreeNode {
        Key key;
        Value val;
        int size; 
        TreeNode* left;
        TreeNode* right;
        TreeNode(Key k, Value v) : key(k), val(v), size(1), left(nullptr), right(nullptr) {}
        TreeNode(Key k, TreeNode* left, TreeNode* right) : key(k), size(1), left(left), right(right) {}
    };

    int size(TreeNode* root) {
        return root == nullptr ? 0 : root->size;
    }

    TreeNode* root;

    AVLTree() : root(nullptr) {}

    void insert(TreeNode*& root, Key key, Value val) {
        if (root == nullptr) {
            root = new TreeNode(key, val);
            return;
        }

        if (key < root->key) {
            insert(root->left, key, val);
        }
        else {
            insert(root->right, key, val);
        }

        root->size = size(root->left) + size(root->right) + 1;

        root = balance(root);
    }

    void remove(TreeNode*& root, Key key) {
        if (root == nullptr) {
            return;
        }
        else if (key < root->key) {
            remove(root->left, key);
        }
        else if (key > root->key) {
            remove(root->right, key);
        }
        else {
            if (root->left != nullptr && root->right != nullptr) {
                TreeNode* successor = root->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                root->key = successor->key;
                root->val = successor->val;
                remove(root->right, successor->key);
            }
            else {
                TreeNode* temp = root;
                if (root->left == nullptr) {
                    root = root->right;
                }
                else if (root->right == nullptr) {
                    root = root->left;
                }
                delete temp;
            }
        }

        if (root != nullptr) {
            root->size = size(root->left) + size(root->right) + 1;
            root = balance(root);
        }
    }

    TreeNode* rightRotation(TreeNode* root) {
        TreeNode* newNode = root->left;
        root->left = newNode->right;
        newNode->right = root;

        root->size = size(root->left) + size(root->right) + 1;
        newNode->size = size(newNode->left) + size(newNode->right) + 1;

        root = newNode;
        return root;
    }

    TreeNode* leftRotation(TreeNode* root) {
        TreeNode* newNode = root->right;
        root->right = newNode->left;
        newNode->left = root;

        root->size = size(root->left) + size(root->right) + 1;
        newNode->size = size(newNode->left) + size(newNode->right) + 1;

        root = newNode;
        return root;
    }

    TreeNode* balance(TreeNode* root) {
        if (root == nullptr) return nullptr;

        root->left = balance(root->left);
        root->right = balance(root->right);
        int balanceFactor = getBalanceFactor(root);

        if (balanceFactor > 1) {
            if (getBalanceFactor(root->left) < 0) {
                root->left = leftRotation(root->left);
            }
            root = rightRotation(root);
        }
        else if (balanceFactor < -1) {
            if (getBalanceFactor(root->right) > 0) {
                root->right = rightRotation(root->right);
            }
            root = leftRotation(root);
        }

        return root;
    }

    int getBalanceFactor(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftHeight = root->left == nullptr ? 0 : root->left->size;
        int rightHeight = root->right == nullptr ? 0 : root->right->size;
        return leftHeight - rightHeight;
    }

    int height(TreeNode* root) {
        if (root == nullptr) return -1;
        return 1 + max(height(root->left), height(root->right));
    }

    void print() {
        queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            int size = queue.size();
            for (auto i = 0; i < size; i++) {
                TreeNode* node = queue.front();
                queue.pop();
                cout << node->key << " ";
                if (node->left)  queue.push(node->left);
                if (node->right) queue.push(node->right);
            }
            cout << endl;
        }
    }

    bool isValidBST(TreeNode* node, TreeNode* minNode, TreeNode* maxNode) {
        if (node == nullptr) {
            return true;
        }

        if ((minNode != nullptr && node->key <= minNode->key) || (maxNode != nullptr && node->key >= maxNode->key)) {
            return false;
        }

        return isValidBST(node->left, minNode, node) && isValidBST(node->right, node, maxNode);
    }

    bool find(TreeNode* root, Key key) {
        if (root == nullptr) {
            return false;
        }
        if (root->key == key) {
            return true;
        }
        if (key < root->key) {
            return find(root->left, key);
        }
        else {
            return find(root->right, key);
        }
    }

};

void handler(string command, AVLTree<string, int> persons, AVLTree<int, string> bounty) {

    vector<string> tokens;
    string token = "";

    for (int i = 0; i < command.length(); i++) {
        if (command[i] == ' ' && isupper(command[i - 1])) {
            tokens.push_back(token);
            token = "";
        }
        else if (command[i] == ',' || (command[i] == ' ' && !isupper(command[i - 1]))) {
            continue;
        } 
        else if (isdigit(command[i]) && command[i - 1] == ' ') {
            tokens.push_back(token);
            token = "";
            token += command[i];
        }
        else  {
            token += command[i];
        }
    }
    tokens.push_back(token);
    // ADD BOUNTY Boba Fett, 54373
    
    for (auto w : tokens) {
        cout << w << " ";
    }
}

int main() {

    AVLTree<string, int> tree_persons;
    AVLTree<int, string> tree_bounty; 

    string command;
    getline(cin, command);

    handler(command, tree_persons, tree_bounty);


	// ---------------------------------------- //
	// -----------   CHECK AVL TREE ----------- //
	// ---------------------------------------- //
	// 
    // 
    // 
    // tree_int.insert(tree_int.root, "apple", 5)     ;
    // tree_int.insert(tree_int.root, "banana", 67)    ;
    // tree_int.insert(tree_int.root, "cherry", 6)    ;
    // tree_int.insert(tree_int.root, "date", 11)      ;
    // tree_int.insert(tree_int.root, "elderberry", 8);
    // tree_int.insert(tree_int.root, "fig", 69)       ;
    // tree_int.insert(tree_int.root, "grape", 3)     ;
    // tree_int.insert(tree_int.root, "honeydew", 14)  ;
    // tree_int.insert(tree_int.root, "ilama", 44)     ;
    // tree_int.insert(tree_int.root, "jackfruit", 13) ;
    //  
    //  
    // tree_int.remove(tree_int.root, "chery");
	// cout << tree_int.isValidBST(tree_int.root, nullptr, nullptr) << endl;
    // tree_int.remove(tree_int.root, "chery");
    // cout << tree_int.isValidBST(tree_int.root, nullptr, nullptr) << endl;
    // tree_int.remove(tree_int.root, "date");
    // cout << tree_int.isValidBST(tree_int.root, nullptr, nullptr) << endl;
    // tree_int.remove(tree_int.root, "ilama");
    // cout << tree_int.isValidBST(tree_int.root, nullptr, nullptr) << endl;
    // tree_int.remove(tree_int.root, "grape");
    // 
    // 
    // 
    // tree_str.insert(tree_str.root, 345, "dfh");
    // tree_str.insert(tree_str.root, 632, "dfg");
    // tree_str.insert(tree_str.root, 634, "hsd");
    // tree_str.insert(tree_str.root, 758, "vcn");
    // tree_str.insert(tree_str.root, 365, "khg");
    // tree_str.insert(tree_str.root, 843, "sdf");
    // tree_str.insert(tree_str.root, 863, "vnc");
    // tree_str.insert(tree_str.root, 766, "shf");
    // tree_str.insert(tree_str.root, 883, "sfg");
    // tree_str.insert(tree_str.root, 223, "bbb");
    // 
    // 
    // tree_str.remove(tree_str.root, 345);
    // cout << tree_str.isValidBST(tree_str.root, nullptr, nullptr) << endl;
    // tree_str.remove(tree_str.root, 632);
    // cout << tree_str.isValidBST(tree_str.root, nullptr, nullptr) << endl;
    // tree_str.remove(tree_str.root, 883);
    // cout << tree_str.isValidBST(tree_str.root, nullptr, nullptr) << endl;
    // tree_str.remove(tree_str.root, 365);
    // cout << tree_str.isValidBST(tree_str.root, nullptr, nullptr) << endl;
    // tree_str.remove(tree_str.root, 223);

} 
