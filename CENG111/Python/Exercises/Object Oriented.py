class Person():
    name = ""
    age= -1
    def Print(self):
        print ("Name:", self.name, "age:", self.age)


class Person5():
    name= ""
    age = 20
    def __eq__(self,other):
        return self.name == other.name and self.age == other.age

class Node():
    def __init__(self, value=""):
        self._left = None
        self._right= None
        self._value = value

    def getLeft(self):
        return self._left
    def setLeft(self,leftNode):
        self._left = leftNode
    def getRight(self):
        return self_right
    def setRight(self, rightNode):
        self._right = rightNode
    def getValue(self):
        return self._value
    def setValue(self,value):
        self._value = value
class Person:
    def __init__(self,name=None, age=None):
        self._name =name
        self._age =age
        self.print()
    def getAge(self):
        return self._age
    def setAge(self,age):
        if type(age) != int: return "Value Error"
        self._age = age
    def print(self):
        print("Name", self._name , "Age:", self._age)
    def __str__(self):
        return "Name"+ self._name + "Age:"+ str(self._age)
    def __eq__(self, obj):
        return self._age ==obj.getAge()

class Student(Person):
    def __init_(self, year= None):
        Person.__init__(self)
        self.year = year