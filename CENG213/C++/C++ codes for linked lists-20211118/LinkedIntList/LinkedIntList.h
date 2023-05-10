#ifndef _LList
#define _LList
#include "ListNode.h"
#include "NoSuchElementException.h"
class LinkedIntList{
public:
    LinkedIntList() {
        front = nullptr;
    }
    ~LinkedIntList();
    LinkedIntList(const LinkedIntList & rhs);
    LinkedIntList & operator=(const LinkedIntList rhs);
    void add (int value);
    void add (int index, int value);
    void addSorted(int value);
    int get (int index);
    int remove(); // throws NoSuchElementException;
    void remove(int index);
    void print();
private:
    ListNode *front;
};
#endif

