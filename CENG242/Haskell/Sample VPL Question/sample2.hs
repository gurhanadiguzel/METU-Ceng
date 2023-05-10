a  = (let   x = 5
            y = 10
            func x = x * x + other y
            other x = x + x
            in  let 
                    other x = x - 1
                    y = 2
                    in func x)

b = let x = 3
        y = 2
        z = 1
        in let y = 1
        in x +let x =5
        in x + y + z

c = let f x = x +1
        g x = x *2
        in f (let f x = x * x in g( f 3))+ f 1

d = let tk n ( x : xs ) | n ==0 = []
                        | otherwise = x :( tk (n -1) xs )
                        in tk 3 [1 ,5 ,2 ,3 ,4 ,0 ,1]

e = let mg a [] = a
        mg [] a = a
        mg ( x : xs ) ( y : ys ) = if x < y then x :(mg xs ( y : ys ))
        else y :(mg ( x : xs ) ys )
        in mg [1 ,5 ,4] [3 ,2]



g = let m n x = case x of
                        [] -> n ==0
                        ( _: r ) -> m (n -1) r
                        in m 3 [1 ,2 ,3 ,4 ,5]


even1 x = (x `mod` 2 == 0)

nmap f [] = []
nmap f ( x : xs ) = ( f x ):(nmap f xs )

nfilter f [] = []
nfilter f ( x : xs ) = if ( f x ) then ( x :( nfilter f xs )) else ( nfilter f xs )


reduce f s [] = s
reduce f s ( x : xs ) = f x ( reduce f s xs )

zpt a [] = [a]
zpt a ( x : xs ) = if a > x then a :( x : xs ) else x :( zpt a xs )


for m n f s = if (m>n) then s else for (m+1) n f ( f m s )

comp f g x y = f x (g x y )

iter 0 f s = s
iter n f s = iter (n -1) f ( f s )



k = nmap even1 [1,2,3,4,5,6]
l = nmap ((+) 2) (nfilter even1 [1,2,3,4,5,6])

m = iter 10 ((*) 2) 4

n = reduce zpt [] [1,3,4,2,3,1]

p = for 10 13 zpt []

r = reduce (comp (*) (+)) 1 [1,2,3]
