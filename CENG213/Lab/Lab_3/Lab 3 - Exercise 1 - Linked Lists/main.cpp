#include <iostream>

#include "LinkedIntList.h"
#include "NoSuchElementException.h"

using namespace std;

int main() {
    LinkedIntList list;


    //list.add(4);

    list.add(18);
    list.add(34);
    list.add(18);
    list.add(18);
    list.add(4);
    list.add(4);


    
    LinkedIntList alist;
    alist.add(34);
    alist.add(34);
    alist.add(18);
    alist.add(18);
    alist.add(4);
    alist.add(4);



    list.print();
    //list.removeAdjacentDuplicates();
    //list.print();
    //list.removeAll(7);
    list.print();
    cout << list.isSorted()<<endl;
    list.invert();
    list.print();
    alist.print();
    cout<< list.equals(alist)<<endl;

    return 0;
}