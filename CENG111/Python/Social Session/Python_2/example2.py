
# EXAMPLE-2 (2018, Quiz-4, Question-3)

# Write a function named "calc" which takes an 8-bit binary number as a STRING,
# an operation as a 1 character string and an integer. This function executes
# the operation specified with the second argument.
# - if operation is "/", it should divide the binary number(first argument) by
#   2^(third argument).
# - if operation is "*":
#   it should multiply the binary number in the first argument with 2^(third
#   argument). If overflow occurs (overflow happens when you need more than
#   8-bits to represent a result), you should return "overflow".
# Note: Here ^ represents exponent operator. In python you should use "**"
#
# SPECIFICATIONS:
# - length of the first argument is always 8.
# - third argument is always positive
# - Your script should return the resulting STRING after the operations.
# - You must not import any modules.
# - You must not use loops, etc.
# - You may use conditional statements
# - You may define functions.
# - You may use built-in functions.
# - You must not print anything.
# - You must not use shift operator.
# - Write your code inside a script and save it as ~/q4.py (under the home directory).
# - Submit your script to CengClass system.
#
# HINT: 'find' method of string.
#

# SOLUTION:
def calc(binStr, operation, n):
    mostSigOne = binStr.find("1")
    if operation == "*":
        if (mostSigOne - n <= -1):
            return 'overflow'
        else:
            return "0"*(mostSigOne-n) + binStr[mostSigOne:] + "0"*n
    else:
        if n >= 8:
            return "00000000"
        else:
            return "0"*(mostSigOne+n) + binStr[mostSigOne:(-1*n)]


# SAMPLE INPUT/OUTPUTs:
# == Input ==
print( calc("00001001", "/", 2) )
# >>>>>>>>>>>>>>><
# == Output ==
# 00000010

# == Input ==
print( calc("00001001", "/", 4) )
# >>>>>>>>>>>>>>><
# == Output ==
# 00000000

# == Input ==
# calc("00001001", "*", 3)
# >>>>>>>>>>>>>>><
# == Output ==
# 01001000

# == Input ==
# calc("00001001", "*", 5)
# >>>>>>>>>>>>>>><
# == Output ==
# overflow
#