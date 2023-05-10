#include <iostream>
#include "Queue.h"
#include "QueueException.h"


using namespace std;

int main()
{
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << q.dequeue() << endl;
    cout  <<  q.peek() << endl;

    Queue<int> q1 (q);
    q1.enqueue(4);

    Queue<int> q2;
    q2 = q1;
    q2.enqueue(5);

    cout<< "printing queue q:" << endl;
    while(!q.isEmpty())
        cout << q.dequeue() << " ";
    cout << endl;

    cout<< "printing queue q1:" << endl;
    while(!q1.isEmpty())
        cout << q1.dequeue() << " ";
    cout << endl;
    cout<< "printing queue q2:" << endl;
    while(!q2.isEmpty())
        cout << q2.dequeue() << " ";
    cout << endl;
}
