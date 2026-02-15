#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(NULL), right(NULL) {}
};

// BST
Node* insertBST(Node* root, int v) {
    if (!root) return new Node(v);
    if (v < root->val) root->left = insertBST(root->left, v);
    else root->right = insertBST(root->right, v);
    return root;
}

// FIND
bool find(Node* root, int key) {
    if (!root) return false;
    if (root->val == key) return true;
    if (key < root->val) return find(root->left, key);
    else return find(root->right, key);
}

// DFS (rekurzivno)
void preorder(Node* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

// DFS
void preorderIter(Node* root) {
    if (!root) return;
    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* cur = st.top(); st.pop();
        cout << cur->val << " ";
        if (cur->right) st.push(cur->right);
        if (cur->left) st.push(cur->left);
    }
}

void inorderIter(Node* root) {
    stack<Node*> st;
    Node* cur = root;

    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top(); st.pop();
        cout << cur->val << " ";
        cur = cur->right;
    }
}

void postorderIter(Node* root) {
    stack<Node*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        Node* cur = st1.top(); st1.pop();
        if (cur->left) st1.push(cur->left);
        if (cur->right) st1.push(cur->right);
        st2.push(cur);
    }

    while (!st2.empty()) {
        cout << st2.top()->val << " ";
        st2.pop();
    }
}

// BFS
void BFS(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        cout << cur->val << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

// SUM
int sumTree(Node* root) {
    if (!root) return 0;
    return root->val + sumTree(root->left) + sumTree(root->right);
}

int main() {
    Node* root = NULL;

    root = insertBST(root, 10);
    root = insertBST(root, 5);
    root = insertBST(root, 15);
    root = insertBST(root, 3);
    root = insertBST(root, 7);

    cout << "Inorder (recursive): ";
    inorder(root); cout << "\n";

    cout << "Preorder (iterative): ";
    preorderIter(root); cout << "\n";

    cout << "BFS: ";
    BFS(root); cout << "\n";

    cout << "Tree sum = " << sumTree(root) << "\n";

    cout << "Find 15 " << (find(root,15) ? "YES" : "NO") << "\n";
}
