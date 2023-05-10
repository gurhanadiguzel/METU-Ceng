#ifndef _DEQUE
#define _DEQUE

#include "DequeException.h"
#include <iostream>
using namespace std;

/*
A deque is a data structure consisting of a list of items, on which the following operations are possible:

push(x): Insert item x on the front end of the deque.
pop(): remove the front item from the deque and return it.
inject(x): Insert item x on the back end of the deque.
eject(): Remove the back item from the deque and return it.

Write the implementation of deque using a circular array.
*/


const int MAX_DEQUE = 100;

class Deque {
public:
    Deque();  // default constructor; copy constructor and destructor are supplied by the compiler

    bool isEmpty() const;	// Determines if deque is empty.
    void push(const int& newItem); // Adds an item to the front of a deque.
    int pop();		   // Removes and returns the front item of a deque.
    void inject(const int& newItem); // Adds an item to the back of a deque.
    int eject();      // Removes and returns the back item from the deque.

    bool isFull(); // Determines if deque is full.
    int getFront(); // Return front element of Deque
    int getBack(); // Return rear element of Deque

private:
    int items[MAX_DEQUE];  	// array of items
    int front;         		// index to front of deque
    int back;                // index to back of deque
    int count;
};


Deque::Deque(){// default constructor
   // TODO:
   front= 0;
   back = MAX_DEQUE-1;
   count=0;
}

bool Deque::isFull() {
    // TODO:
    if(count==MAX_DEQUE){
        return true;
    }
    return false;
}

bool Deque::isEmpty() const {
   // TODO:
    if(count ==0){
       return false;
    }
    return true;
}

int Deque::getFront() {
    // TODO:
    return items[front];
}

int Deque::getBack() {
    // TODO:
    return items[back];
}

int Deque::pop() {
    // TODO:
    int val = items[front];
    front = (front+1) % MAX_DEQUE;
    count--;
    return val; 
}

void Deque::push(const int& newItem) {
    // TODO:
    
    front = (front-1) %MAX_DEQUE;
    if(front<0){front+=MAX_DEQUE;}
    items[front] = newItem;
    count++;
}


int Deque::eject() {
    // TODO:
    int val = items[back];
    back = (back-1) % MAX_DEQUE;
    count--;
    return val; 
 }

void Deque::inject(const int& newItem) {
    // TODO:
    back = (back+1) %MAX_DEQUE;
    items[back] = newItem;
    count++;

}
#endif // _EXCEPTION

