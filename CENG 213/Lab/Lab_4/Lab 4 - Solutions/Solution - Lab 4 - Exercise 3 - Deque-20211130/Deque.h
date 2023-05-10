#ifndef DEQUE_H
#define DEQUE_H

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
    Deque(); // default constructor; copy constructor and destructor are supplied by the compiler

    bool isEmpty() const;               // Determines if deque is empty.
    void push(const int& newItem);      // Adds an item to the front of a deque.
    int pop();                          // Removes and returns the front item of a deque.
    void inject(const int& newItem);    // Adds an item to the back of a deque.
    int eject();                        // Removes and returns the back item from the deque.

    bool isFull();  // Determines if deque is full.
    int getFront(); // Return front element of Deque
    int getBack();  // Return rear element of Deque

private:
    int items[MAX_DEQUE];   // array of items
    int front;              // index to front of deque
    int back;               // index to back of deque
};

Deque::Deque() { // default constructor
   /* TODO */

   front = -1;
   back = 0;
}

bool Deque::isFull() {
    /* TODO */

    return ((front == 0 && back == MAX_DEQUE-1) || front == back+1);
}

bool Deque::isEmpty() const {
    /* TODO */

    return (front == -1);
}

int Deque::getFront() {
    /* TODO */

    if (isEmpty()) {
        throw DequeException("DequeException: deque empty on getFront");
    }
    return items[front];
}

int Deque::getBack() {
    /* TODO */

    if (isEmpty() || back < 0) {
        throw DequeException("DequeException: deque empty on getBack");
    }
    return items[back];
}

int Deque::pop() {
    /* TODO */

    // Check whether Deque is empty or not.
    if (isEmpty()) {
        throw DequeException("DequeException: deque empty on pop");
    }

    // Deque has only one element.
    if (front == back) {
        front = -1;
        back = -1;

        return items[0];
    } else {
        int item = items[front];

        front = (front + 1) % MAX_DEQUE;

        return item;
    }
}

void Deque::push(const int& newItem) {
    /* TODO */

    // Check whether Deque is full or not.
    if (isFull()) {
        throw DequeException("DequeException: deque full on push");
    }

    // If queue is initially empty.
    if (front == -1) {
        front = 0;
        back = 0;
    } else {
       front = (MAX_DEQUE + ((front - 1) % MAX_DEQUE)) % MAX_DEQUE;
    }
    items[front] = newItem;
}


int Deque::eject() {
    /* TODO */

    if (isEmpty()) {
        throw DequeException("DequeException: deque empty on eject");
    }
    int index;
    // Deque has only one element.
    if (front == back) {
        front = -1;
        back = -1;

        index = 0;
    } else {
        index = back;

        back  = (MAX_DEQUE + ((back - 1) % MAX_DEQUE)) % MAX_DEQUE;
    }
    return items[index];
}

void Deque::inject(const int& newItem) {
    /* TODO */

    if (isFull()) {
        throw DequeException("DequeException: deque full on insert");
    }

    // If queue is initially empty.
    if (front == -1) {
        front = 0;
        back = 0;
    } else {
        back = (back + 1) % MAX_DEQUE;
    }
    items[back] = newItem;
}

#endif //DEQUE_H
