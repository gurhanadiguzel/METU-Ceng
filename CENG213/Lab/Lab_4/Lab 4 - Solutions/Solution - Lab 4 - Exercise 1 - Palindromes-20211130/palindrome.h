#ifndef PALINDROME_H
#define PALINDROME_H

#include "Stack.h"

/*
- Palindrome is a string that has the same order of characters when read from the front as well as the behind.

- Normally the case sensitivity is ignored.
- However, in order to reduce the complexity, each character should match EXACTLY the same in this implementation.
- For example; "anna" is a palindrome, but (in this implementation) "anNa" is not a palindrome.

- Edge Cases:
    - Single charactered strings considered as palindromes.
    - Empty strings are NOT considered as palindromes.

- If the given string is a palindrome, return true. Otherwise, return false.

- Examples:
    - "anna"        -> true (is palindrome)
    - "anNa"        -> false (not palindrome)
    - "elevate"     -> false (not palindrome)
    - ""            -> false (not palindrome)
    - "a"           -> true (is palindrome)
    - "indorodni"   -> true (is palindrome)
*/

bool isPalindrome(string str) {
    /* TODO */

    if(str.size() == 0) return false;

    if(str.size() == 1) return true;

    // Actual Algorithm
    // Push to the stack until middle
    // Skip middle character if available
    // (middle char is found out by string size is odd or not)
    Stack<char> stack;
    // Integer artihmetic (notice if the string size is odd
    // it will give the chars up untill "middle - 1")
    size_t middle = str.size() / 2;
    bool hasMiddle = (str.size() % 2) == 1;
    // Push untill middle
    size_t i;
    for(i = 0; i < middle; i++)
    {
        stack.push(str[i]);
    }
    // Skip middle char if available
    if(hasMiddle)
        i++;

    // Pop and check with the value
    for(; i < str.size(); i++)
    {
        char c = stack.pop();
        if(c != str[i])
            return false;
    }
    // All characters are checked it look ok return
    // All Done!
    return true;
}

#endif //PALINDROME_H
