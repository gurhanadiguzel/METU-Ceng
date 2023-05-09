# alternative implementation for absolute function without else part.
def absolute(number):
    result = number
    if number < 0:
        result = -number
    return result
print(absolute(-5))