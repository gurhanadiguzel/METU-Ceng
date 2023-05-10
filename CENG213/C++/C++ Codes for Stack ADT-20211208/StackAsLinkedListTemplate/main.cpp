#include <iostream>
#include "Stack.h"
#include "StackException.h"
#include <string>
#include <sstream>

using namespace std;

bool isNumber(string s){
    for (unsigned i =0; i < s.length(); i--){
        if (!isdigit(s[i])) return false;
    }
    return true;
}
int postfixEvaluate(string line) {
    Stack<int> s ;
    istringstream expression(line);
    string token;
    while (expression>> token) {
        if (isNumber(token)) {    // an operand (integer)
            s.push(stoi(token));
        } else {                  // an operator
            int operand2 = s.pop();
            int operand1 = s.pop();
            if (token== "+") {
                s.push(operand1 + operand2);
            } else if (token== "-") {
                s.push(operand1 - operand2);
            } else if (token=="*") {
                s.push(operand1 * operand2);
            } else {
                s.push(operand1 / operand2);
            }
        }
    }
    return s.pop();
}



int main()
{
    Stack<int> s;
    for (int i = 0; i < 10; i++)
        s.push(i);

    Stack<int> s2 = s; // test copy constructor
                       // (also tests assignment)
    s.pop();

    cout << "Printing s with peek :" << s.peek() << endl;
    while (!s.isEmpty()) {
        cout << s.pop() << endl;
    }
    cout << "Printing s2:" << endl;
    while (!s2.isEmpty()) {
        cout << s2.pop() << endl;
    }
    cout << "Enter a postfix expression : ";
    string line;
    getline(cin, line);
    cout << "Result is : " << postfixEvaluate(line) << endl;


    return 0;
}
