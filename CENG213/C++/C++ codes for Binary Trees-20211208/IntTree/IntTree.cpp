#include "IntTreeNode.h"
#include "IntTree.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

IntTree::IntTree(IntTreeNode *r )
{
    root = r;
}

//Constructor that creates a full binary tree of a given height
IntTree::IntTree(int height)
{
    /* initialize random seed: */
    srand (time(NULL));
    root = nullptr;
    construct(root, height);
}

//Destructor
IntTree::~IntTree()
{
    deleteTree(root);
}

// Copy constructor
IntTree::IntTree(const IntTree & t)
{
    if(t.root == nullptr)
        root = nullptr;
    else
        make_copy(root,t.root);
}

// Assignment operator
IntTree& IntTree::operator=(const IntTree& t)
{
    if(this !=&t)
    {
        deleteTree(root);
        make_copy(root,t.root);
    }
    return *this;
}

// Returns the height of this tree
int IntTree::height()
{
    return(height(root));
}

// Returns if this tree contains value val
bool IntTree::contains(int val)
{
    return contains(root, val);
}

// Prints this tree in inorder
void IntTree::print()
{
    printInOrder(root);
    cout << endl;
}

// Prints this tree sideways
void IntTree::printSideways()
{
    printSideways(root,"");
}

// Returns the maximum value in this binary tree
int IntTree::getMax()
{
    return (getMax(root));
}

// Finds the sum of all values in this tree
int IntTree::find_sum()
{
    return find_sum(root);
}



// Private methods

// Helper method to construct a binary tree with a given height
void IntTree::construct(IntTreeNode *&r, int h)
{
    if (h>-1)
    {
        r = new IntTreeNode(rand() % 100 + 1);  // data value is in range 1..100
        construct(r->left,h-1);                 // construct left subtree
        construct(r->right,h-1);                // construct right subtree
    }
}

// Helper method to delete all nodes in a tree
void IntTree::deleteTree(IntTreeNode *&r)
{
    if (r == nullptr)
        return;
    deleteTree(r->left);
    deleteTree(r->right);
    delete r;
    r = nullptr;
}

// Make t1 a deep copy of t2
void IntTree::make_copy(IntTreeNode *& r1, IntTreeNode * r2)
{
    if(r2!=nullptr)
    {
        r1=new IntTreeNode(r2->data);
        make_copy(r1->left,r2->left);
        make_copy(r1->right,r2->right);
    }
    else
        r1=nullptr;

}

// Helper method to return the height of the tree
// TODO
int IntTree::height(IntTreeNode * r)
{

    return -1;
}


// Helper method to print the nodes in inorder
void IntTree::printInOrder(IntTreeNode * r)
{
    if (r!=nullptr)
    {
        printInOrder(r->left);
        cout << r->data << " " ;
        printInOrder(r->right);
    }
}

// Helper method to print the nodes sideways
void IntTree::printSideways(IntTreeNode *r, string str)
{
    if (r != nullptr)
    {
        printSideways(r->right, str+"   ");
        cout << str << r->data <<  endl;
        printSideways(r->left, str + "   ");
    }
}

// Helper method to return if this binary search tree contains the value val
// TODO
bool IntTree::contains(IntTreeNode *r, int val)
{
    return true;
}

// Helper method to find the maximum value in this binary tree
int IntTree::getMax(IntTreeNode *r)
{
    int root_val, left, right, maxi;
    maxi = -1; // Assuming all values are positive integers

    if (r!=NULL)
    {
        root_val = r ->data;
        left = getMax(r->left);
        right = getMax(r->right);
        // Find the largest of the three values.
        if (left > right)
            maxi = left;
        else
            maxi = right;
        if (root_val > maxi)
            maxi = root_val;
    }
    return maxi;
}

// Helper method to find the overall sum of  values
int IntTree::find_sum(IntTreeNode *r)
{
    if (r==nullptr)
        return 0;
    else
        return (find_sum(r->left) + find_sum(r->right) + r->data);
}



