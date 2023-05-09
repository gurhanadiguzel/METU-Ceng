# EXAMPLE-3 (2013, Quiz-4, Question-3)

# Write a function that takes two arguments whose name is "isSpaceEnough". 
# The first argument is available free space on hardisk which is a string. 
# It can be in terms of MB or GB. 
# The second parameter is also a string which is the size of the folder to be copied which can be in terms of MB, GB.(e.g. 15 MB) 
# Your aim is to find if the file will fit the space or not. Your function should return a tuple of two elements. 
# The first element is "Successful" if the space is enough and "Failure" otherwise. 
# Second element will be remaining space(in terms of MB) if the operation is successful 
# and required space if the operation is failure.  1 GB = 1.024 MB

def isSpaceEnough(availableSpace, size): 
    spaceList =  availableSpace.split(" ") # spaceList = ["1", "GB"]
    sizeList = size.split(" ") # sizeList = ["500", "MB"]

    if spaceList[1] == "GB":
        space = int(spaceList[0]) * 1024
    else:
        space = int(spaceList[0])

    if sizeList[1] == "GB":
        sizeMB = int(sizeList[0]) * 1024
    else:
        sizeMB = int(sizeList[0])

    requiredORremaining = space - sizeMB

    if requiredORremaining < 0:
        return ('Failure', abs(requiredORremaining))
    else:
        return ('Successful', requiredORremaining)


print(isSpaceEnough("5 GB", "5000 MB"))  # ('Succesful', 524)
