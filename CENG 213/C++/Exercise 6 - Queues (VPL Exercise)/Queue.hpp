#ifndef _QUEUE
#define _QUEUE

#include "QueueException.hpp"

const int MAX_QUEUE = 100;

template <class T>
class Queue {
public:
    Queue();                        // Default constructor; copy constructor and destructor are supplied by the compiler.

    bool isEmpty() const;           // Determines if queue is empty.
   	void enqueue(const T& newItem); // Adds an item to the end of queue.
   	T dequeue();                    // Removes and returns the item at the beginning of queue.
    T peek() const;                 // Returns the item at the beginning of queue without removing it.
    int size() const;               // Returns the number of items in queue.

private:
   	T items[MAX_QUEUE];             // array of queue items
   	int front;                      // index to beginning of queue
   	int back;                       // index to end of queue
   	int count;                      // number of items in queue
};

template <class T>
Queue<T>::Queue():front(0), back(MAX_QUEUE-1), count(0) { // Default constructor.

}

template <class T>
bool Queue<T>::isEmpty() const { // Determines if queue is empty.

    return count == 0;
}

template <class T>
void Queue<T>::enqueue(const T& newItem) { // Adds an item to the end of queue.

    if (count == MAX_QUEUE)
        throw QueueException("QueueException: queue full on enqueue");
    else { // queue is not full; insert item
        back = (back+1) % MAX_QUEUE;
        items[back] = newItem;
        ++count;
    }
}

template <class T>
T Queue<T>::dequeue() { // Removes and returns the item at the beginning of queue.

    if (isEmpty())
        throw QueueException("QueueException: empty queue, cannot dequeue");
    else { // queue is not empty; remove front
        T val = items[front];
        front = (front+1) % MAX_QUEUE;
        --count;
        return val;
    }
}

template <class T>
T Queue<T>::peek () const { // Returns the item at the beginning of queue without removing it.

    if (isEmpty())
        throw QueueException("QueueException: empty queue, cannot getFront");
    else // queue is not empty; retrieve front
        return (items[front]);
}

template<class T>
int Queue<T>::size() const { // Returns the number of items in queue.
    return count;
}

#endif //_QUEUE

