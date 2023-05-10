#include <iostream>
#include "LinkedIntList.h"
#include "NoSuchElementException.h"
using namespace std;

int main(){

    LinkedIntList list;

    list.add(5);
    list.add(10);
    list.add(15);
    list.print();
    cout <<"second element is " << list.get(1) << endl;
    list.addSorted(12);
    list.print();
    list.addSorted(100);
    try{
        list.remove(0);
        list.remove();
        list.remove();
        list.remove();
        list.print();
    }
    catch (NoSuchElementException e){
        cout << "List is empty!!"<< endl;
    }
}
