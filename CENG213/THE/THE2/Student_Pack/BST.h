#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.    
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void copy(BSTNode<T> *&newnode, BSTNode<T> *obj);
    bool isEmpty(BSTNode<T> *node)const;
    bool contains(BSTNode<T> *node, BSTNode<T> *node1) const;
    void insert(BSTNode<T> *&node, const T &data);
    void remove(BSTNode<T> *&node, const T &data);
    void removeAllNodes(BSTNode<T> *&node);
    BSTNode<T>* search(BSTNode<T> *node, const T &data) const;
    BSTNode<T>* getSuccessor(BSTNode<T> *node,BSTNode<T> *node1, TraversalPlan tp) const;
    BSTNode<T>* getMin(BSTNode<T> *node) const;
    BSTNode<T>* find_parentnode(BSTNode<T> *node,BSTNode<T> *node1) const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    /* TODO */
    this->root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    /* TODO */
    copy(this->root, obj.root); 
}

template<class T>
BST<T>::~BST() {
    /* TODO */
    removeAllNodes(root);
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    /* TODO */
    return this->root;
}

template<class T>
bool BST<T>::isEmpty() const {
    /* TODO */
    return isEmpty(root);
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    /* TODO */
    return contains(root, node);
}

template<class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    return insert(root, data);
}

template<class T>
void BST<T>::remove(const T &data) {
    /* TODO */
    return remove(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    /* TODO */
    return removeAllNodes(root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    /* TODO */
    return search(root,data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {    
    if (tp == inorder) {
        /* TODO */
        return getSuccessor(root, node, tp);
    } else if (tp == preorder) {
        /* TODO */
        return getSuccessor(root, node, tp);
    } else if (tp == postorder) {
        /* TODO */
        return getSuccessor(root, node, tp);
    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {
    if (tp == inorder) {
        if (isEmpty()) {
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } 
    else if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } 
    else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    if (this != &rhs) {
        removeAllNodes(root);
        copy(root, rhs.root);
    }
    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {
    // check if the node is NULL?
    if (node == NULL){return;}   

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        // then, output the node.
        std::cout << "\t" << node->data;
        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    else if (tp == preorder) {
        /* TODO */        
        std::cout << "\t" << node->data;
        if (node->left) {
            std::cout << "," << std::endl;
        }       
        print(node->left, preorder);
         if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } 
    else if (tp == postorder) {
        /* TODO */        
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }        
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }    
        std::cout << "\t" << node->data;
    }
}

template<class T>
void BST<T>::copy(BSTNode<T> *&newnode, BSTNode<T> *obj){
    if (obj == NULL){
        newnode = NULL;
    }
    else{
        newnode = new BSTNode<T>;
        newnode->data = obj->data;
        copy(newnode->left, obj->left);
        copy(newnode->right, obj->right);
    } 
}

template<class T>
bool BST<T>::isEmpty(BSTNode<T> *node)const{
    if(node == NULL){
        return true;
    }
    return false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node, BSTNode<T> *node1) const{
    if(node == NULL){
        return false;
    }
    if(node == node1){
        return true;
    }
    if(node1->data > node->data){
        return contains(node->right, node1);
    }
    if(node1->data < node->data){
        return contains(node->left, node1);
    }
}

template<class T>
void BST<T>::insert(BSTNode<T> *&node, const T &data){
    if(node == NULL){
        node = new BSTNode<T>(data,NULL,NULL);
    }
    else if (data == node-> data){
        return;
    }
    else if(data > node->data){
        insert(node->right, data);
    }
    else if(data < node->data){
        insert(node->left, data);
    }

}

template<class T>
void BST<T>::remove(BSTNode<T> *&node, const T &data){
    if(node == NULL){
        return;
    }
    else if (data > node->data){
        remove(node->right, data);
    }
    else if (data < node->data){
        remove(node->left, data);
    }
    else{
        if (node->left !=NULL && node->right != NULL) {
            node->data = getMin(node->right)->data;
            remove(node->right, node->data);
        }
        else {
            BSTNode<T> * oldNode =node;
            node = (node->left != NULL)? node->left : node->right;
            delete oldNode;
            oldNode= NULL;
        }
    }        
}

template<class T>
void BST<T>::removeAllNodes(BSTNode<T> *&node){
    if(node == NULL){
        return;
    }
    removeAllNodes(node->right);
    removeAllNodes(node->left);
    delete node;
    node = NULL;
}

template<class T>
BSTNode<T>* BST<T>::search(BSTNode<T> *node, const T &data) const{
    if(node ==NULL){
        return NULL;
    }
    else if(node ->data == data){
        return node;
    }
    else if(data > node->data){
        return search(node->right, data);
    }
    else if(data < node->data){
        return search(node->left, data);
    }
}

template<class T>
BSTNode<T>* BST<T>::getSuccessor(BSTNode<T> *node,BSTNode<T> *node1, TraversalPlan tp) const{
    if (tp == inorder) {
        if(node1->right != NULL){
            return getMin(node1->right);
        }       
        else{
            BSTNode<T>* succ = find_parentnode(node,node1);
            while (succ != NULL && node1 == succ->right) {
                node1 = succ;
                succ = find_parentnode(node,succ);
            }
            return succ;
        }
    } 
    else if (tp == preorder) {
        if(node1->left != NULL){
            return node1->left;
        }
        if(node1->right != NULL){
            return node1->right;
        }
        else{
            BSTNode<T>* parent = find_parentnode(node,node1);
            while (parent != NULL && parent != node) {
                node1 = find_parentnode(node,node1);
                parent = find_parentnode(node,parent);
                if(node1 == parent->left && parent->right){
                    return parent->right;
                }
            }
            if (parent == node || parent == NULL){
                return NULL;
            }            
            return parent->right;
        }
    } 
    else if (tp == postorder) {
        if (node1 == root){
            return NULL;
        }
        else{
            BSTNode<T>* parent = find_parentnode(node,node1);
            if (parent->right == NULL || parent->right == node1){
                return parent;
            }
            BSTNode<T>* succ = parent->right;
            while (succ->left != NULL || succ->right != NULL){
                if(succ->left){
                    succ = succ->left;
                }
                else{
                    succ = succ->right;
                }           
            }           
            return succ;
        }        
    }
}

template<class T>
BSTNode<T>* BST<T>::getMin(BSTNode<T> *node) const{
    if (node->left == NULL) {
        return node;
    } 
    else {
        return getMin(node->left);
    }
}

template<class T>
BSTNode<T>* BST<T>::find_parentnode(BSTNode<T> *node,BSTNode<T> *node1) const{
    if(node == NULL || node1 == NULL || node1 == node){
        return NULL;
    }
    if(node->left == node1 || node->right == node1){
        return node;
    }
    else if(node1->data > node->data){
        find_parentnode(node->right, node1);
    }
    else if(node1->data < node->data){
        find_parentnode(node->left, node1);
    }
}

