#ifndef _STACK
#define _STACK
#include "StackException.h"
#include <iostream>
using namespace std;

template <class T>
class StackNode
{
  public:
    StackNode(const T& e = T(), StackNode* n = nullptr){
      item = e;
      next = n;
    }
    T item;
    StackNode* next;
};


template <class T>
class Stack{
public:
   Stack();             					// default constructor
   Stack(const Stack& rhs);  				// copy constructor
   ~Stack();                    			// destructor
   Stack& operator=(const Stack& rhs); // assignment operator
   bool isEmpty() const;
   void push(const T& newItem);
   T  pop();
   T  peek() const;
private:
   StackNode<T> *topPtr;       // pointer to the first node in
                               // the stack
};
template <class T>
Stack<T>::Stack(){    // default constructor
  topPtr=nullptr;
}

template <class T>
bool Stack<T>::isEmpty() const
{
   return topPtr == nullptr;
}

template <class T>
void Stack<T>::push(const T& newItem) {
   // create a new node
   StackNode<T> *newPtr = new StackNode<T>;

   newPtr->item = newItem; // insert the data

   newPtr->next = topPtr; // link this node to the stack
   topPtr = newPtr;       // update the stack top
}
template <class T>
T Stack<T>::pop() {
   if (isEmpty())
      throw StackException("StackException: stack empty on  pop");
   else {
      T stackTop = topPtr->item;
      StackNode<T> *tmp = topPtr;
      topPtr = topPtr->next; // update the stack top
      delete tmp;
      return stackTop;
   }
}

template <class T>
T  Stack<T>::peek() const  {
   if (isEmpty())
      throw StackException("StackException: stack empty on getTop");
   else
      return(topPtr->item);
}

template <class T>
Stack<T>::~Stack() {
   // pop until stack is empty
   while (!isEmpty())
       pop();
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) {
   if (this != &rhs) {
      while (!isEmpty()) pop();
	   if (!rhs.topPtr)  topPtr = nullptr;
      else {
            topPtr = new StackNode<T>;
            topPtr->item = rhs.topPtr->item;
            StackNode<T>* q = rhs.topPtr->next;
            StackNode<T>* p = topPtr;
            while (q) {
                p->next = new StackNode<T>;
                p->next->item = q->item;
                p = p->next;
                q = q->next;
            }
            p->next = nullptr;
        }
    }
    return *this;
}

template <class T>
Stack<T>::Stack(const Stack<T>& rhs) {
    topPtr = new StackNode<T> ;
    *this = rhs; // reuse assignment operator
}

#endif
