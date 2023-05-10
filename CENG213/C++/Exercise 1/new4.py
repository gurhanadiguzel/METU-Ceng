import math

x=float(input('Enter the lenght from the center to vertex:'))
s = float(2*x*(math.sin(math.pi/5)))
area = (3*math.sqrt(3)/2*s*s)
print('The area of the pentagon is',area)
