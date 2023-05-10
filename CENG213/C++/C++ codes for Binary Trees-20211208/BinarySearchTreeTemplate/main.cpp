#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
    BinarySearchTree<int> myTree;

    for (int i = 50; i > 0; i=i-5 )
        myTree.add(i);
    for (int i = 55; i < 100; i=i+5 )
        myTree.add(i);
    myTree.print();
    myTree.printSideways();
    cout << "Height of the tree is: " << myTree.height() << endl;
    cout << "Depth of 75 is: " << myTree.depth(75) << endl;
    myTree.remove(50);
    myTree.printSideways();
    cout << "50 is " << (myTree.contains(50)? "":" NOT ")<< "in the tree" << endl;
    cout << "5 is " << (myTree.contains(5)? "":" NOT ")<< "in the tree" << endl;
    if (!myTree.isBalanced()){
        myTree.makeItBalanced();
        cout << "Balanced tree:\n";
        myTree.printSideways();
    }
    BinarySearchTree<int> myTree2(myTree);
    cout<<"Testing copy constructor:\n";
    myTree2.printSideways();

    cout<<"Testing assignment operator:\n";
    BinarySearchTree<int> myTree3;

    myTree3 = myTree2;
    myTree3.printSideways();


}
