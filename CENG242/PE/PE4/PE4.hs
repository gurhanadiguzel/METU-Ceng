module PE4 where

import Data.List
import Data.Maybe

data Room = SeedStorage Int
          | Nursery Int Int
          | QueensChambers
          | Tunnel
          | Empty
          deriving Show

data Nestree = Nestree Room [Nestree] deriving Show

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------

-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _

---------------------------------------------------------------------------------------------

-- Q1: Calculate the nutrition value of a given nest.
getNutVal:: Nestree -> Int 
getNutVal (Nestree (SeedStorage a) l) = 3*a
getNutVal (Nestree (Nursery a b) l) = 7*a + 10*b
getNutVal x = 0
 
nestNutritionValue :: Nestree -> Int
nestNutritionValue (Nestree room []) = getNutVal (Nestree room [])
nestNutritionValue (Nestree room  (x:xs)) = getNutVal (Nestree room (x:xs)) + nestNutritionValue x + nestNutritionValue(Nestree Empty xs)
    
-- Q2: Calculate the nutrition value of each root-to-leaf path.
pathNutritionValues :: Nestree -> [Int]
pathNutritionValues (Nestree room lst) = pathHelper (Nestree room lst) 0

pathHelper :: Nestree ->Int -> [Int]
pathHelper( Nestree room []) count     = [getNutVal (Nestree room []) + count]
pathHelper (Nestree room (x:xs)) count 
    | null xs = pathHelper x (val + count)
    |otherwise = pathHelper x (val + count) ++ pathHelper (Nestree room xs) (count)
    where
        val = getNutVal (Nestree room (x:xs)) 


-- Q3: Find the depth of the shallowest tunnel, if you can find one.
shallowestTunnel :: Nestree -> Maybe Int
shallowestTunnel (Nestree room lst)
    |null result  = Nothing
    |otherwise  = Just (minimum result)
    where 
        result = shallowestHelper (Nestree room lst) 1

shallowestHelper :: Nestree -> Int ->[Int]
shallowestHelper (Nestree Tunnel []) count =  [count]
shallowestHelper (Nestree room []) count =  []
shallowestHelper (Nestree Tunnel (x:xs)) count  = [count] ++ shallowestHelper x (count+1)  ++ shallowestHelper (Nestree Tunnel xs) (count)
shallowestHelper (Nestree room (x:xs)) count  = shallowestHelper x (count+1)  ++ shallowestHelper (Nestree room xs) (count)

-- Q4: Find the path to the Queen's Chambers, if such a room exists.
pathToQueen :: Nestree -> Maybe [Room]
pathToQueen (Nestree QueensChambers []) = Just []
pathToQueen (Nestree room lst)
    |null result = Nothing 
    |otherwise = Just (result) 
    where
        result = queenHelper (Nestree room lst) []

queenHelper :: Nestree -> [Room]-> [Room]
queenHelper (Nestree QueensChambers []) path = path
queenHelper (Nestree room []) path = []
queenHelper (Nestree QueensChambers (x:xs)) path = path
queenHelper (Nestree room (x:xs)) path = queenHelper x (path++[room])++ queenHelper (Nestree room xs) path

-- Q5: Find the quickest depth to the Queen's Chambers, including tunnel-portation :)
quickHelper :: Nestree -> [Room]
quickHelper (Nestree QueensChambers []) = []
quickHelper (Nestree room lst)
    |null result = []
    |otherwise = result
    where
        result = queenHelper (Nestree room lst) []

tunnelHelper :: Nestree -> Int
tunnelHelper nest
    |not (isNothing tunnel1 )&& (tunnelHelper2 tunnel2 0 /= 0) = (tunnelHelper2 tunnel2 0) + fromJust(tunnel1) +1
    |otherwise = 0
    where
        tunnel1 = shallowestTunnel(nest)
        tunnel2 = reverse (queenHelper(nest) [])

tunnelHelper2 :: [Room]->Int -> Int
tunnelHelper2 (Tunnel:xs) count= count
tunnelHelper2 (x:[]) count= 0
tunnelHelper2 (x:xs) count = tunnelHelper2 xs (count+1)

quickQueenDepth :: Nestree -> Maybe Int
quickQueenDepth (Nestree QueensChambers x) = Just 1
quickQueenDepth (lst)
    |isNothing (pathToQueen lst) = Nothing
    |count2 == 0 = Just count 
    |otherwise = Just (minimum[count2, count])
    where
        count =length (quickHelper lst)+1
        count2 = tunnelHelper lst
        
-- Example nest given in the PDF.
exampleNest :: Nestree
exampleNest = 
  Nestree Tunnel [
    Nestree (SeedStorage 15) [
      Nestree (SeedStorage 81) []
    ],
    Nestree (Nursery 8 16) [
      Nestree Tunnel [
        Nestree QueensChambers [
          Nestree (Nursery 25 2) []
        ]
      ]
    ],
    Nestree Tunnel [
      Nestree Empty [],
      Nestree (SeedStorage 6) [
        Nestree Empty [],
        Nestree Empty []
      ]
    ]
  ]

-- Same example tree, with tunnels replaced by Empty
exampleNestNoTunnel :: Nestree
exampleNestNoTunnel = 
  Nestree Empty [
    Nestree (SeedStorage 15) [
      Nestree (SeedStorage 81) []
    ],
    Nestree (Nursery 8 16) [
      Nestree Empty [
        Nestree QueensChambers [
          Nestree (Nursery 25 2) []
        ]
      ]
    ],
    Nestree Empty [
      Nestree Empty [],
      Nestree (SeedStorage 6) [
        Nestree Empty [],
        Nestree Empty []
      ]
    ]
  ]
