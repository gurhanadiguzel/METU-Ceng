#include "palindrome.h"

using namespace std;

int main() {
    
    string expr = "anna";

    if (isPalindrome(expr))
        cout << "Palindrome";
    else
        cout << "Not Palindrome";
    
    return 0;
}