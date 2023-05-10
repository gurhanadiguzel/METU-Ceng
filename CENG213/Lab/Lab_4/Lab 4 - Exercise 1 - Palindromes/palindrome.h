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
    int high = str.length() - 1;
    if(high <0){
        return false;
    }
    
    Stack<char> string1;
    Stack<char> string2;
    Stack<char> string3;
    
    for(int i=0;i<=high;i++){
        string1.push(str[i]);
        string2.push(str[i]);
    }
    while(!string2.isEmpty()){
        string3.push(string2.pop());
    }
    
	while (!string1.isEmpty()){
		if (string1.pop()!=string3.pop()){
			return false;
		}
	}
	return true;
}

#endif //PALINDROME_H