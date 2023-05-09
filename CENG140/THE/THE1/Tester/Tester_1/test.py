import os

inp = open("input.txt", "r")

ilist = inp.read().split(" |\n")

inp.close()

for i in range(len(ilist)-1):

    xd = open("xd.txt", "w")
    xd.write(ilist[i])
    xd.close()
    os.system('./the1.exe <xd.txt>> output.txt')
    o = open("output.txt", "a")
    o.write(" |\n")
    o.close()

file1 = open('case1.txt', 'r')
file2 = open('output.txt', 'r')
a1 = file1.read()
a2 = file2.read()
case1 = a1.split(" |\n")
outs = a2.split(" |\n")

for i in range(len(outs)-1):
    if outs[i] == case1[i]:
        print("Test "+str(i+1)+" Passed!")

    else:
        print("Test "+str(i+1)+" Failed!")











