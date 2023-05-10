#include "IntTreeNode.h"
#include <iostream>
#include <string>
using namespace std;

class IntTree
{
public:
    //Default constructor
    IntTree(IntTreeNode *r = nullptr);
    //Constructor that creates a full binary tree of a given height
    IntTree(int height=-1);
    //Destructor
    ~IntTree();
    // Copy constructor
    IntTree(const IntTree & t);
    // Assignment operator
    IntTree& operator=(const IntTree& t);
    // Returns the height of this tree
    int height();
    // Returns if this tree contains value val
    bool contains(int val);
    // Prints this tree in inorder
    void print();
    // Prints this tree sideways
    void printSideways();
    // Returns the maximum value in this binary tree
    int getMax();
    // Finds the sum of all values in this tree
    int find_sum();

private:
    // Private data member:
    // the overall root of the tree. It is null for an empty tree
    IntTreeNode *root;

    // Private methods

    // Helper method to construct a full binary tree with a given height
    void construct(IntTreeNode *&r, int h);
    // Helper method to delete all nodes in a tree
    void deleteTree(IntTreeNode *&r);
    // make a deep copy of a given tree
    void make_copy(IntTreeNode *& t1, IntTreeNode * t2);
    // Helper method to return the height of the tree
    int height(IntTreeNode * r);
    // Helper method to print the nodes in inorder
    void printInOrder(IntTreeNode * r);
    // Helper method to print the nodes sideways
    void printSideways(IntTreeNode *r, string str);
    // Helper method to return if this binary search tree contains the value val
    bool contains(IntTreeNode *r, int val);
    // Helper method to find the maximum value in this binary tree
    int getMax(IntTreeNode *r);
    // Helper method to find the overall sum of  values
    int find_sum(IntTreeNode *r);

};
