#ifndef _BST
#define _BST

class IntTreeNode {
    public:
       int data;             // data stored at this node
       IntTreeNode *left;    // reference to left subtree
       IntTreeNode *right;   // reference to right subtree

    // Constructs a leaf node with the given data.
    IntTreeNode(int val=0) {
       data = val;
       left = nullptr;
       right = nullptr;
    }

    // Constructs a branch node with the given data and links.
    IntTreeNode(int val, IntTreeNode *lf, IntTreeNode *rt) {
        data = val;
        left = lf;
        right = rt;
    }
};
#endif
