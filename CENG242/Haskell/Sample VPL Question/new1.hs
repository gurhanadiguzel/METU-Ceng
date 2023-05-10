data Tree a = Node (a , Tree a , Tree a) | Empty deriving Show

x =5 ; y =6 ; z = 3
t = let x =1
        in let y =2
            in x+y+ z