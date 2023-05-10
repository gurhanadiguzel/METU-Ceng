[10:19, 21.03.2022] +90 532 288 18 78: //gcc 7.4.0

#include  <stdio.h>
struct s1 {int a; int b;} ;  //glb.s1
void f(struct s1 p){}
int main(void)
{
    struct s1 {int a; int b;} v1; v1.a=10; // main.s1
   f (v1);
    return 0;
}
[10:19, 21.03.2022] +90 532 288 18 78: --ghc 8.0.2
x = 10*(if (3>4) then 10 else 5)
f x= x+1
g x= 2*x
z = ((if (x>10)  then f else g) 5)+10
y = (if (x<10) then (*) else (\x y->x+y)) 10 20
data MyList = Empty | LL (Int, MyList) deriving Show
xx = LL (3, LL (2, LL (3, Empty)))
convert a = case a of 
    Empty -> []
    LL (x, y) -> x:(convert y)
    
x1= [1,2,3]
x2 = [x| x<-x1, x> 2]

main = print $ x2
[10:19, 21.03.2022] +90 532 288 18 78: --ghc 8.0.2
f1 (x,y) = x+y
f2 x y = x+y
f3 = f2 2
-- Curry'ed function
g a b c d = a+b+c+d  -- g=\a b c d -> a+b+c+d g::Int->Int->Int->Int->Int
h2 = g 2 3  -- h =\c d ->2+3+c+d
gg = \a b c d-> a+b+c+d
hh = gg 2 3
hg = \c d ->2+3+c+d
h = g 2 3 2 -- hhh::Int->Int   \d-> 2+3+2+d

main = print $ h2 2 3
[10:20, 21.03.2022] +90 532 288 18 78: --ghc 8.0.2
fact1 x = if (x==0) then 1 else ((fact1 (x-1))*x)

fact2 0 = 1
fact2 x = (fact2 (x-1))*x

fact3 x = case x of
      0-> 1      
      _-> (fact3 (x-1))*x 

 

fact4 x | x==0 = 1   -- Boolean expression = expression/body of fun
        | otherwise = (fact4 (x-1))*x

main = print $ (fact1 0, fact2 0, fact3 0, fact4 0)