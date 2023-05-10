data T1 = A1 | B1 T2 deriving Show
data T2 = A2 | B2 T1 deriving Show
x =  B1 (B2 (B1 (B2 (B1 A2)))) --sum:7
-- A1 -> 0, A2-> 0, B1->1, B2-> 2
f1 A1 =0
f1 (B1 x) = 1+ (f2 x)
f2 A2 =0
f2 (B2 x) = 2+(f1 x)
y = Node (5, Node( 5, Node (3, Empty, Empty), Empty), z)
z = Node (2, Empty, Empty)
data BTree a = Empty | Node (a, BTree a, BTree a) deriving Show
num Empty = 0
num (Node (x,y,z)) = 1+(num y)+(num z)

sumT Empty = 0
sumT (Node (x,y,z)) = x+(sumT y)+(sumT z)

xx = Node (True, Empty, Node (False, Empty, Empty))


main = print $ num xx

--ghc 8.0.2
f x = x+1
ff = \x->x+1
x=2
g y  = y 2

main = print $ (f 2, ff 2, (\x->x+1) 2, f x, g f, g (\x->x+1))

type TT = (Int, Bool)
type TT2 = (Int, Bool)

data T2 = Ax | Bx T2 deriving Show
data T = A | B T deriving Show

--lengthT::T->Int
lengthT A = 0
lengthT (B x)= 1+ (lengthT x)

data L a = LL  | RR (a, L a) deriving Show

lengthL::(L a)-> Int

lengthL (LL) = 0
lengthL (RR (x,y)) = 1+ (lengthL y)

mylength [] = 0
mylength (x:y) = 1+ (mylength y)

main = print $  'a':"abc" --mylength [1,3,45] --1:(2:(1:[])))