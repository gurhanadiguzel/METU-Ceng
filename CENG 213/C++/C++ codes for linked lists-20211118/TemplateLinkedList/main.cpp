#include <iostream>
#include "MyLinkedList.h"

using namespace std;

int main()
{
    MyLinkedList<int> list;
    for (int i = 1; i<11; i++)
        list.add(i);

    cout << "Testing copy constructor \n";
    MyLinkedList<int> list2(list);
    list.print();
    list2.print();

    list.add(5,11);

    cout<< "Testing operator= \n";
    MyLinkedList<int> list3;
    list3 = list;
    list.print();
    list3.print();

    list.remove();
    list3.remove(list.get(2));

    cout <<"Finally:\n";
    list.print();
    list2.print();
    list3.print();

    return 0;
}
