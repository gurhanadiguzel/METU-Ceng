#include "QueueException.h"
#include "QueueNode.h"

template <class T>
class Queue {
public:
   Queue();                             // default constructor
   Queue(const Queue& rhs);             // copy constructor
   ~Queue();                            // destructor
   Queue& operator=(const Queue & rhs); //assignment operator

	bool isEmpty() const;
 	void enqueue(const T& newItem);
	T dequeue() throw(QueueException) ;
	T peek() const throw(QueueException);
	int size();
private:
	QueueNode<T> *backPtr;
    QueueNode<T> *frontPtr;
};

template<class T>
Queue<T>::Queue() : backPtr(nullptr), frontPtr(nullptr){}

template<class T>
Queue<T>::~Queue() {	     // destructor
   while (!isEmpty())
      dequeue();   // backPtr and frontPtr are null at this point
}

template<class T>
bool Queue<T>::isEmpty() const{
   return backPtr == nullptr;
}
template<class T>
void Queue<T>::enqueue(const T& newItem) {
   	// create a new node
   	QueueNode<T> *newPtr = new QueueNode<T>;

  	    // set data portion of new node
   	newPtr->item = newItem;
   	newPtr->next = nullptr;

   	// insert the new node
  	    if (isEmpty())		// insertion into empty queue
      	   frontPtr = newPtr;
   	else			// insertion into nonempty queue
      	   backPtr->next = newPtr;

   	backPtr = newPtr;  	// new node is at back
}
template<class T>
T Queue<T>::dequeue() throw(QueueException) {
   if (isEmpty())
   	throw QueueException("QueueException: empty queue, cannot dequeue");
   else {  	// queue is not empty; remove front
      QueueNode<T> *tempPtr = frontPtr;
      T queueFront = frontPtr->item;
      if (frontPtr == backPtr) {  	// one node in queue
         frontPtr = nullptr;
         backPtr = nullptr;
      }
      else
         frontPtr = frontPtr->next;

      tempPtr->next = nullptr;  	// defensive strategy
      delete tempPtr;
      return queueFront;
    }
}
template<class T>
T Queue<T>::peek() const throw(QueueException) {
   if (isEmpty())
      throw QueueException("QueueException: empty queue, cannot peek");
   else 	// queue is not empty; retrieve front
      return(frontPtr->item);
}

template<class T>
int Queue<T>::size(){
    QueueNode<T> * cur = frontPtr;
    int cnt =0;
    while(cur){
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rhs) {
   if (this != &rhs) {
      while (!isEmpty()) dequeue();
      if (!rhs.isEmpty())  {
            QueueNode<T> * cur = rhs.frontPtr;
            enqueue(cur->item);
            cur = cur->next;
            while (cur) {
                enqueue(cur->item);
                cur = cur->next;
            }
       }
    }
    return *this;
}

template <class T>
Queue<T>::Queue(const Queue<T>& rhs) {
    frontPtr = nullptr;
    backPtr = nullptr;
    *this = rhs; // reuse assignment operator
}


