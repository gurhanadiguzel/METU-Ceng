#ifndef _BST
#define _BST
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include "NoSuchElementException.h"
using namespace std;
template <class T>
class TreeNode {
    public:
       T data;             // data stored at this node
       TreeNode<T> *left;    // reference to left subtree
       TreeNode<T> *right;   // reference to right subtree

    // Constructs a leaf node with the given data.
    TreeNode<T>(T val=T()) {
       data = val;
       left = NULL;
       right = NULL;
    }

    // Constructs a branch node with the given data and links.
    TreeNode<T>(T val, TreeNode<T> *lf, TreeNode<T> *rt) {
        data = val;
        left = lf;
        right = rt;
    }
};

template <class T>
class BinarySearchTree{
public:
      BinarySearchTree<T>(){
          root = NULL;
      }

      //Destructor
      ~BinarySearchTree<T>(){
        deleteTree(root);
      }

      BinarySearchTree<T>(const BinarySearchTree<T> & t){
          if(t.root == NULL)
            root = NULL;
          else make_copy(root,t.root);
      }

      BinarySearchTree& operator=(const BinarySearchTree& t){
          if(this !=&t){
            deleteTree(root);
            make_copy(root,t.root);
          }
          return *this;
      }

      // Returns the height of this tree
      int height(){
         return(height(root));
      }

      // Returns the depth of a node with the given value in this tree
      int depth(T val){
         return depth(root, val, 0);
      }

      // Adds the given value to this BST in sorted order.
      void add(T value) {
        add(root, value);
      }

      void remove(T value) {
         remove(root, value);
      }

      // Returns if this tree contains value val
      bool contains(T val){
         return contains(root, val);
      }

      T getMin() {
        if (root == NULL)
           throw new NoSuchElementException();
        return getMin(root);
      }

      // Prints this tree in inorder
      void print(){
         printInOrder(root);
         cout << endl;
      }

      // Prints this tree sideways
      void printSideways(){
          printSideways(root,"");
      }

      bool isBalanced(){
          int h= -1;
          return isBalanced(root,h);
      }

      void makeItBalanced(){
        int i;
        vector<T> A;
        putInArray(root, A);
        deleteTree(root);
        i=0;
        makeItBalanced(root, A, A.size(), i);
      }

private:
       // Private data member:
       // the overall root of the tree. It is null for an empty tree
       TreeNode<T> *root;

       // Private methods

       // Helper method to add a new node with the given value
       void add(TreeNode<T> *&r, T value) {
          if (r == NULL) {
             r = new TreeNode<T>(value);
          } else if (r->data > value) {
             add(r->left, value);
          } else if (r->data < value) {
             add(r->right, value);
          } // else a duplicate
       }

       void remove(TreeNode<T> *& r, T value) {
          if (r == NULL)
             return;
          else if (r->data > value)
             remove(r->left, value);
          else if (r->data < value)
             remove(r->right , value);
          else    // r->data == value; remove this node
             if (r->left !=NULL && r->right != NULL) {
               // both children; replace w/ min from R
                r->data = getMin(r->right);
                remove(r->right, r->data);
               }
             else {
                TreeNode<T> * oldNode =r;  // only  R or L child
                r = (r->left != NULL)? r->left : r->right;
                delete oldNode;
             }
        }

       // Helper method to delete all nodes in a tree
       void deleteTree(TreeNode<T> *&r){
         if (r == NULL)
            return;
         deleteTree(r->left);
         deleteTree(r->right);
         delete r;
         r = NULL;
       }

       void make_copy(TreeNode<T> *& r1, TreeNode<T> *r2){
          if(r2!=NULL){
            r1=new TreeNode<T>(r2->data);
            make_copy(r1->left,r2->left);
            make_copy(r1->right,r2->right);
          }
          else r1=NULL;
       }

       // Helper method to return the height of the tree
       int height(TreeNode<T> * r){
          if (r == NULL)
            return -1;
          else return (max(height(r->left), height(r->right)) + 1);
       }

       // Helper method to find the depth of a given value
       int depth(TreeNode<T> * r, int val, int d){
          if (r==NULL)
            return -1;
          if (r->data == val)
            return d;
          int ld = depth(r->left, val, d+1);
          if (ld != -1)
            return ld;
          return (depth(r->right, val, d+1));
       }

       // Helper method to print the nodes in inorder
       void printInOrder(TreeNode<T> * r){
          if (r!=NULL){
            printInOrder(r->left);
            cout << r->data << " " ;
            printInOrder(r->right);
          }
       }

       // Helper method to print the nodes sideways
       // TODO
       void printSideways(TreeNode<T> *r, string str){
          if (r != NULL){
            printSideways(r->right, str+"   ");
            cout << str << r->data <<  endl;
            printSideways(r->left, str + "   ");
          }
       }

       // Helper method to return if this binary search tree contains the value val
       bool contains(TreeNode<T> *r, T val){
          if (r == NULL)
            return false;
          else {
            if (r->data == val)
                return true;
            else if (r->data > val)
                return contains(r->left,val);
            else return contains(r->right,val);
          }
        }

        T getMin(TreeNode<T>* r) {

           if (r->left == NULL) {
              return r->data;
           } else {
             return getMin(r->left);
           }
        }

        // Helper method to determine if this  tree is balanced
        bool isBalanced(TreeNode<T> *r, int &h){
           int lh=-1, rh=-1;
           if (r == NULL){
               h = -1;
               return true;
           }
           bool lt, rt;
           lt = isBalanced(r->left, lh);
           rt = isBalanced(r->right,rh);
           h = max(lh,rh) + 1;
           if (lt && rt && abs(lh-rh)<2)
               return true;
           else
               return false;
        }

        void putInArray(TreeNode<T> *&r, vector<T> & A){
          if (r!=NULL){
            putInArray(r->left, A);
            A.push_back( r->data) ;
            putInArray(r->right, A);
          }
        }

        // Helper method to make it a balanced search tree

        void makeItBalanced(TreeNode<T> *&r, vector<T> &A, int n, int &i){
          if (n>0){
             r = new TreeNode<T>();
             makeItBalanced(r->left, A, n/2, i);
             r->data = A[i];
             i++;
             makeItBalanced(r->right, A, (n - 1)/2, i);
          }

        }

 };
#endif

