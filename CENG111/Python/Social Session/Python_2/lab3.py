# EXAMPLE-1 (2013, Quiz-4, Question-1)

#A student must attend a seminar in a week and s/he should stay at least 60 minutes in a seminar to be accepted. 
#The time that students enter and leave are recorded. Your aim is to write a function whose name is "isAccepted" 
#which takes one parameter as a list in the form of [<hour>:<minute>,<hour>:<minute>] 
#Note that the enter and leave times are not ordered in the list. 
#You should PRINT "Accepted" if the time that is spent is greater than or equal to 60 minutes, 
#otherwise you should PRINT "Rejected". Your function should also RETURN number of minutes spent on that seminar

"""[entering, leaving]
[leaving, entering]"""

# ["3:56", "4:45"]
def isAccepted(listTimes):
    time1 = listTimes[0].split(":") # time1 = ["3", "56"]
    time2 = listTimes[1].split(":") # time2 = ["4", "45"]

    totalTimes1 = int(time1[0]) * 60 + int(time1[1])
    totalTimes2 = int(time2[0]) * 60 + int(time2[1])

    timeSpent = abs(totalTimes1 - totalTimes2)

    if timeSpent >= 60:
        print("Accepted")
        return timeSpent
    else:
        print("Rejected")
        return timeSpent

print(isAccepted(["3:56", "4:45"])) #rejected and return 49
print(isAccepted(["14:25", "12:55"])) #Accepted and return 90


