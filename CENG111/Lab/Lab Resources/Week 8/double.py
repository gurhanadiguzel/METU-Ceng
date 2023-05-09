# an example for accessing a global variable to change its value. 
# please work on this code by removing the line including global keyword and see why we need it.

myint = 5

def doublemyint():
    global myint
    myint = myint * 2
    return myint

print(doublemyint())