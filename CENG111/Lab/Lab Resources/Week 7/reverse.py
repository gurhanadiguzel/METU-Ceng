#Write a script named 'reverse.py' that reads a string from the user and prints True if the string is palindrome, False otherwise.
inp = input()
print(inp == inp[::-1])
