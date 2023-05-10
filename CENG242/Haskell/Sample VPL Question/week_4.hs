[10:20, 28.03.2022] +90 532 288 18 78: //gcc 7.4.0

#include  <stdio.h>

int fib (int n)
{
    if (n==0) return 0;
    if (n==1) return 1;
    return (fib(n-1)+fib(n-2));
}

long long int fib2(int n)
{
    long long int i, t, f=0, s=1;
    for (int i=n;i>=1;i--)
    {
        t=s;
        s=f+s;
        f=t;
    }
    return f;
}


int main(void)
{
    printf("%d \n", fib2(10));
    return 0;
}
[10:20, 28.03.2022] +90 532 288 18 78: --ghc 8.0.2
fib 0 = 0
fib 1 = 1
fib n = fib (n-1)+fib (n-2)

-- n -- nth fib numb -- (n+1)st fib number
fib2 0 f s = f
--fib2 1 f s = s
fib2 n f s = fib2 (n-1) s (f+s)

--- rev takes n iteratins (calls ++) if the list has n elements
--- total cost of rev is n^2
rev [] = []
rev (a:b) = (rev b) ++ [a]

--- (+++) takes n iterations if the first list has length n
[] +++ c = c
(a:b) +++ c = a:(b +++ c)

--- par1: input, par2: output
tailrev [] r = r
tailrev (a:b) r = tailrev b (a:r)

main = print $ tailrev [1,2,3] []
[10:20, 28.03.2022] +90 532 288 18 78: data TAKA = Taka TUKA | Tak Int
data TUKA = Tuka TAKA | Tuk Bool

taka = Taka (Tuka (Taka (Tuka (Taka (Tuk True)))))
tuka = Tuka taka

f (Tak x) = x
f (Taka y) = 2*(g y)

g (Tuk True) =1
g (Tuk False) = 0
g (Tuka x) = 1+ (f x)


main = print $ f taka
[10:20, 28.03.2022] +90 532 288 18 78: --ghc 8.0.2
s=[1,2,3,4,10,2]
t = [x+1 | x<-s, x>3]

-- left to right : outer to inner loop
x=[(x,y)| x<-[1,2,3,4], y<-[10,20,30]]

myconcat xss = [x| xs<-xss,x<-xs]
myconcat3 xsss = [x| xss<-xsss,xs<-xss, x<-xs]

myzip:: [a]->[b]->[(a,b)]  -- a and b are type variables

myzip [] _ = []
myzip _ [] = []
myzip (a:b) (c:d) = (a,c):(myzip b d)

-- position 3 [1,4,5,3,7,2,3,6] ===> [4,7]  
--list of indexes where x appears in xs

position x xs = [i| (x',i)<-zip xs [1..n], x == x']
    where n = length xs
    
main = print $ [1..10]
--position 3 [1,4,5,3,7,2,3,6]
-- zip [1,4,5,3,7,2,3,6] [1,2,3,4,5,6,7,8] ==> [ (1,1),(4,2),...]
-- (x',i) <-[ (1,1),(4,2),...] ==> (1,1)...(4,2)...
-- .. (3,4) --> x==x' (3 ==3) is True, so i=4
-- 4 is placed into the new list


--myzip [1,2,3,4,5] ["aa","bb","cc","dd"]

--myconcat3 [[[1,2,3],[4,5],[6,7,8]], [[1]]]
--[(x,y)| x<-[1,2,3,4], x>2,y<-[10,20,30],10*x>y]

