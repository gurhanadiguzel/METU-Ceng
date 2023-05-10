#include <iostream>

#include "BST.h"

int main() {
    BST<int> tree;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    tree.insert(10);
    tree.insert(5);
    tree.insert(7);
    tree.insert(6);
    tree.insert(15);
    tree.insert(13);
    tree.insert(14);
    //tree.remove(7);
    //std::cout<<tree.find<<std::endl;
    std::cout<<tree.getSuccessor(tree.search(15),preorder)->data<<std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
