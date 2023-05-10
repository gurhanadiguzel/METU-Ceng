#include <iostream>
#include "IntTreeNode.h"
#include "IntTree.h"
using namespace std;

int main()
{
    int height = 2;
    cout << "Here is a random full tree of height 2:" << endl;
    IntTree myFullTree(height);
    cout << "Inorder traversal: " << endl;
    myFullTree.print();
    cout << "\nFull Tree Sideways: " << endl;
    myFullTree.printSideways();

    cout << "Height of the full binary tree is " << myFullTree.height() << endl;

    int val = 0;
    cout << "Enter a value to search in the full binary tree: ";
    cin >> val;
    cout << myFullTree.contains(val) << endl;

    // Write code to test other methods

    return 0;
}
