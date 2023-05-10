#include <iostream>

#include "Functions.hpp"

using namespace std;

// Each of the following 3 problems indicates what kind of structure to use as auxiliary storage.
// You should not use any other auxiliary data structure to solve the problems,
// although you can create as many simple variables as you would like.

// Write a function called "collapse" that accepts a stack of integers as a parameter and
// collapses it by replacing each successive pair of integers with the sum of the pair.
// For example if the stack stores [7, 2, 8, 9, 4, 11, 7, 1, 42] such that 42 is at the top and
// 7 is at the bottom, the first pair should be collapsed into 9 (7+2), the second pair
// should be collapsed into 17 (8+9), and so on. If the stack stores and odd number of elements,
// the final element is not collapsed (such as the 42 in our example). So for this stack,
// your function would yield [9, 17, 15, 8, 42], where 9 is at the bottom and 42 is at the top.
// You can only use one queue as auxiliary storage.
// You are not allowed to use any other auxiliary data structures.
void collapse(Stack<int>& s) {
    /* TODO */
    Queue<int> q;
    while(!s.isEmpty()){
        q.enqueue(s.pop());
    }
    while(!q.isEmpty()){
        s.push(q.dequeue());
    }
    while(!s.isEmpty()){
        int temp = s.pop();
        if(!s.isEmpty()){
            q.enqueue(temp+s.pop());
        }
        else{
            q.enqueue(temp);
        }
    }
    while(!q.isEmpty()){
        s.push(q.dequeue());
    }
    
}

// Write a function called "reorder" that accepts a queue of integers as a parameter and
// puts the integers in the given queue into nondecreasing sorted order. 
// For this function, you may assume that the given queue is already sorted in nondecreasing order by absolute values. 
// For example if the queue stores [1, 2, -2, 4, -5, 8, -8, 12, -15],
// (notice that the values appear in nondecreasing sorted order if you ignore the signs of the numbers),
// your function should reorder the values so that the queue stores [-15, -8, -5, -2, 1, 2, 4, 8, 12].
// Use one stack as auxiliary storage.
void reorder(Queue<int>& q) {
    /* TODO */
    Stack<int> s;
    Stack<int> s1;
    while(!q.isEmpty()){
        int temp = q.dequeue();
        if(temp>0){
            s.push(temp);
        }
        else{
            s1.push(temp);
        }
    }
    while(!s1.isEmpty()){
        q.enqueue(s1.pop());
    }
    while(!s.isEmpty()){
        s1.push(s.pop());
    }
    while(!s1.isEmpty()){
        q.enqueue(s1.pop());
    }
}

// Write a function called "copyStack" that accepts a stack of integers as a parameter and 
// returns a copy of the original stack. The original stack must be restored to its original state. 
// You may use one queue as auxiliary storage.
Stack<int> copyStack(Stack<int> &s) {
    /* TODO */
    Queue<int> q;
    Stack<int> copy;
    while(!s.isEmpty()){
        copy.push(s.pop());
    }
    while(!copy.isEmpty()){
        int temp = copy.pop();
        q.enqueue(temp);
        s.push(temp);
    }
    while(!q.isEmpty()){
        copy.push(q.dequeue());
    }
    return copy;
}
