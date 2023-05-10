#include <iostream>

#include "Functions.hpp"

using namespace std;

int main() {
    /************/
    /* collapse */
    /************/
    cout << "Creating an empty stack named s1." << std::endl;
    Stack<int> s1;
    
    cout << "Creating a stack named s2 with values (top to bottom): 1" << std::endl;
    Stack<int> s2;
    s2.push(1);
    
    cout << "Creating a stack named s3 with values (top to bottom): 1, 2" << std::endl;
    Stack<int> s3;
    s3.push(2);
    s3.push(1);
    
    cout << "Creating a stack named s4 with values (top to bottom): 1, 2, 3" << std::endl;
    Stack<int> s4;
    s4.push(3);
    s4.push(2);
    s4.push(1);
    
    cout << "Collapsing s1, s2, s3, and s4." << endl;
    collapse(s1);
    collapse(s2);
    collapse(s3);
    collapse(s4);

    cout << "Stack s1 (after collapse):" << endl;
    while (!s1.isEmpty()) {
        cout << s1.pop() << endl;
    }
    cout << "Stack s2 (after collapse):" << endl;
    while (!s2.isEmpty()) {
        cout << s2.pop() << endl;
    }
    cout << "Stack s3 (after collapse):" << endl;
    while (!s3.isEmpty()) {
        cout << s3.pop() << endl;
    }
    cout << "Stack s4 (after collapse):" << endl;
    while (!s4.isEmpty()) {
        cout << s4.pop() << endl;
    }
    
    /***********/
    /* reorder */
    /***********/
    cout << "Creating a queue named q1 with values (front to back): 1, 2, -2, 4, -5, 8, -8, 12, -15" << std::endl;
    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(-2);
    q1.enqueue(4);
    q1.enqueue(-5);
    q1.enqueue(8);
    q1.enqueue(-8);
    q1.enqueue(12);
    q1.enqueue(-15);

    cout << "Reordering q1." << endl;
    reorder(q1);

    cout << "Queue q1 (after reorder):" << endl;
    while (!q1.isEmpty()) {
        cout << q1.dequeue() << " ";
    }
    cout << endl;
    
    /*************/
    /* copyStack */
    /*************/
    
    cout << "Creating a stack named s5 with values (top to bottom): 7, 2, 8" << std::endl;
    Stack<int> s5;
    s5.push(8);
    s5.push(2);
    s5.push(7);

    cout << "Taking a copy of s5 and naming it s6." << std::endl;
    Stack<int> s6 = copyStack(s5);
    
    cout << "Stack s5 (after copyStack):" << endl;
    while (!s5.isEmpty()) {
        cout << s5.pop() << endl;
    }
    cout << "Stack s6 (after copyStack):" << endl;
    while (!s6.isEmpty()) {
        cout << s6.pop() << endl;
    }

    return 0;
}