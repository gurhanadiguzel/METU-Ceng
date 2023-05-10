data D= A Int | B Bool deriving Show

data MyEnum = Sun | Mon | Tue | Thr | Fri deriving Show

data X1 = AA Int | BB (Int, Bool) | CC deriving Show

data X2 = A1 Int | B1 (Int, Bool) | C1 (Int->Int)


xx= (C1 f)


fx2 (A1 x) = x

fx2 (B1 (x,y)) = -x

fx2 (C1 x) = x 10


day::MyEnum->Int

--day Sun = 0

day Mon = 1

day Tue = 2

day Fri = 5



fx (AA x) = x

fx (BB (x,y)) = x

--fx (BB (x, False) ) = -x

fx CC = 0


df (A y) = y

df (B True) = 1

df (B False) = 0


dg (A y) = (A (y+1))  -- D

dg (B y) = (B y)   -- D


--dh (A y) = y  -- Int

--dh (B y) = y -- Bool


d=a+5

c=b

a::Int

a=2

b::(Int,Bool)

b=(2, True)



f::Int->Int

f a = a+1

g x = 1

h::()->Int

h () = 1

--second::(x,y)->y

second (a,b) = b



main = print $ fx2 (C1 h)