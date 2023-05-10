#include "Stack.h"
#include "StackException.h"
#include <iostream>

using namespace std;

int max(Stack<int> & s) {
    Stack<int> backup;
    int maxValue = s.pop();
    backup.push(maxValue);

    while (!s.isEmpty()) {
        int next = s.pop();
        backup.push(next);
        maxValue = max(maxValue, next);
    }

    while (!backup.isEmpty()) {
        s.push(backup.pop());
    }
    return maxValue;
}

int main() {
    Stack<int> s;
    for (int i = 0; i < 10; i++)
        s.push(i);

    Stack<int> s2 = s; // test copy constructor
                       // (also tests assignment)
    cout << "max value in s is " << max(s) << endl;
    cout << "Peeking " << s.peek() << endl;
    cout << "Printing s:" << endl;

    while (!s.isEmpty()) {
        cout << s.pop() << endl;
    }

    cout << "Printing s2:" << endl;
    while (!s2.isEmpty()) {
        cout << s2.pop() << endl;
    }

    return 0;
}

