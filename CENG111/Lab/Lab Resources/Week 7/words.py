# Write a script named "words.py" that reads a sentence composed of three words and prints each word ub separate lines using slicing.
sentence = raw_input()
first = sentence.find(' ')
print(sentence[:first])
second = sentence[first+1:].find(' ')
print(sentence[first+1:first+second+1])
print(sentence[first+second+2:])
