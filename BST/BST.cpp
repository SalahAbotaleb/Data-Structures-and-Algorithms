#include <bits/stdc++.h>

using namespace std;
/**
 * The goal of BST is to represent data in sorted way in
 * a tree where we can query(search) the tree in O(logn)
 * and insert in O(logn) and delete in O(logn)
 * The idea simply is to insert a TreeNode in its correct position
 * The disadvantage is that insertion order affects the complexity
 * and can cause the complexities of all operations to be O(n) instead of O(logn)
 * the solution is to balance the tree
 * there are many alternatives we can address them later:
 * 1. AVL trees
 * 2. Red Black trees
 * 3. B/B+ trees
 * where all of them depend on idea of having self balancing tree
 * to be able to achieve operations in O(1)
 * */
struct TreeNode {
    TreeNode *left = NULL;
    TreeNode *right = NULL;
    int val;
    TreeNode(int val){
        this->val=val;
    }
    TreeNode(){}
};

class BST {
private:
    TreeNode *root = NULL;
    enum Direction {
        LEFT, RIGHT, ROOT
    };

    void insert(TreeNode *curr, TreeNode *toAddNode) {
        if (toAddNode->val < curr->val) {
            if (curr->left == NULL) {
                curr->left = toAddNode;
                return;
            }
            insert(curr->left, toAddNode);
            return;
        }
        if (curr->right == NULL) {
            curr->right = toAddNode;
            return;
        }
        insert(curr->right, toAddNode);
        return;
    }

    void print(TreeNode *curr, ostream &out) {
        if (curr == NULL) return;
        print(curr->left, out);
        out << curr->val << " ";
        print(curr->right, out);
    }

    bool find(TreeNode *curr, int val) {
        if (curr == NULL) return false;
        if (curr->val == val) return true;
        if (val < curr->val) {
            return find(curr->left, val);
        }
        return find(curr->right, val);
    }

    TreeNode *removeLeftMost(TreeNode *curr) {
        if (curr->left == NULL) return curr;
        /**
         *  in case of having the left most containing a right child
         * */
        if(curr->left && curr->left->left == NULL){
            TreeNode* left = curr->left;
            curr->left = curr->left->right;
            return left;
        }
        return removeLeftMost(curr->left);
    }

    TreeNode *getReplacementNode(TreeNode *curr) {
        if (curr->left == NULL && curr->right == NULL) return NULL;
        if (curr->left == NULL) return curr->right;
        if (curr->right == NULL) return curr->left;
        TreeNode* leftMost = removeLeftMost(curr->right);
        return leftMost;
    }

    void remove(TreeNode *parent, TreeNode *curr, int val, Direction direction) {
        if (curr == NULL) return;
        if (curr->val == val) {
            TreeNode *replacementNode = getReplacementNode(curr);
            if (direction == ROOT) {
                root = replacementNode;
            } else if (direction == LEFT) {
                parent->left = replacementNode;
            } else {
                parent->right = replacementNode;
            }
            if(replacementNode!=NULL){
                if(replacementNode != curr->left)
                replacementNode->left = curr->left;
                if(replacementNode != curr->right)
                replacementNode->right = curr->right;
            }
            return;
        }

        if (val < curr->val) {
            remove(curr, curr->left, val, LEFT);
        }else{
            remove(curr, curr->right, val, RIGHT);
        }
    }

public:
    void insert(TreeNode *node) {
        if (root == NULL) {
            root = node;
            return;
        }
        insert(root, node);
    }

    bool find(int val) {
        return find(root, val);
    }

    void remove(int val) {
        remove(NULL, root, val, ROOT);
    }

    void print() {
        print(root, cout);
        cout<<endl;
    }
};

int main() {
    BST bst;
    TreeNode* n1 = new TreeNode(10);
    TreeNode* n2 = new TreeNode(12);
    TreeNode* n3 = new TreeNode(8);
    TreeNode* n4 = new TreeNode(11);
    TreeNode* n5 = new TreeNode(7);
    TreeNode* n6 = new TreeNode(9);
    TreeNode* n7 = new TreeNode(6);
    bst.insert(n1);
    bst.print();
    bst.remove(n1->val);
    bst.print();

    bst.insert(n1);
    bst.insert(n2);
    bst.insert(n3);
    bst.insert(n4);
    bst.insert(n5);
    bst.insert(n6);
    bst.print();
    bst.remove(10);
    bst.print();
    bst.remove(8);
    bst.print();
    bst.remove(9);
    bst.print();
    bst.insert(n7 );
    bst.print();
}