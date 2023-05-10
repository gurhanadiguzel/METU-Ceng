#include <iostream>
#include "LinkedIntList.h"
using namespace std;


void LinkedIntList::add(int value){
    if (front == nullptr) {
        // adding to an empty list
        front = new ListNode(value);
    }
    else {
        // adding to the end of an existing list
        ListNode *current = front;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new ListNode(value);
    }
}

void LinkedIntList::add(int index, int value) {
    if (index == 0) {
        // adding to an empty list
        front = new ListNode(value, front);
    }
    else {
        // inserting into an existing list
        ListNode *current = front;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        current->next = new ListNode(value,current->next);
    }
}

void LinkedIntList::addSorted(int value){
    ListNode* current;
    if (front == nullptr||front->data >= value) {
        // adding to an empty list
        front = new ListNode(value, front);
    }
    else{
        current = front;
        while (current->next && current->next->data < value) {
            current = current->next;
        }
        current->next = new ListNode(value,current->next);
    }
}


int LinkedIntList::get(int index) {
    ListNode *current = front;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

int LinkedIntList::remove() {
    if (front == nullptr) {
        throw NoSuchElementException();
    }
    else {
        int result = front->data;
        ListNode *tmp = front;
        front = front->next;
        delete tmp;
        return result;
    }
}

void LinkedIntList::remove(int index) {
    if (index == 0) {
        // special case: removing first element
        ListNode* tmp = front;
        front = front->next;
        delete tmp;
    }
    else {
        // removing from elsewhere in the list
        ListNode *current = front;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        ListNode *tmp = current->next;
        current->next = current->next->next;
        delete tmp;
    }
}

void LinkedIntList::print(){
    ListNode * current = front;
    while (current != nullptr){
        cout << current->data << " " ;
        current = current->next;
    }
    cout << endl;
}

LinkedIntList::~LinkedIntList(){
    while(front)
        remove();
}

LinkedIntList::LinkedIntList(const LinkedIntList & rhs){
    front = nullptr;
    *this = rhs; // use operator=
}

LinkedIntList& LinkedIntList::operator=(const LinkedIntList rhs){
  if (this != &rhs) {
    while(front)
        remove();
    ListNode* r = rhs.front;

    while (r) {
       add(r->data);
       r = r->next;
    }
  }
  return *this;
}
