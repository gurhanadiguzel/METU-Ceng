module PE3 where

-- can use these if you want to...
import Data.List
import Data.Maybe

data Private = Private { idNumber :: Int, height :: Int, timeToSwap :: Int } deriving Show

data Cell = Empty | Full Private deriving Show

type Area = [[Cell]] 

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------


-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _


--------------------------
-- Part I: Warming up with Abstractions

-- bubbleHumans: Applying a parallel bubble step on integers.
bubbleHumans :: [Int] -> [Int]
bubbleHumans []= []
bubbleHumans  [x]= [x]
bubbleHumans (x:y:xs)
    | y>x = y:x:bubbleHumans(xs)
    | otherwise = x:bubbleHumans(y:xs) 

-- bubblePrivates: The same thing, but on privates with a key function and an asc/desc option.
bubblePrivates :: (Private -> Int) -> Bool -> [Private] -> [Private]
bubblePrivates fields bool [] = [] 
bubblePrivates fields bool [x] = [x]
bubblePrivates fields bool (x:y:xs)  
    | bool && (fields y > fields x) = y: x: bubblePrivates fields bool xs
    | not bool && (fields y < fields x) = y: x: bubblePrivates fields bool xs
    | otherwise = x: bubblePrivates fields bool (y:xs)

-- sortPrivatesByHeight: Full sort via multiple bubble steps, calculate the sorting time too!
sortPrivatesByHeight :: [Private] -> ([Private], Int)
sortPrivatesByHeight lst = sortPrivatesByHeight2 lst 0


sortPrivatesByHeight2 :: [Private] -> Int -> ([Private], Int)
sortPrivatesByHeight2 lst sum
    |sortingHelper lst 0 == 0 = (lst, sum)
    |otherwise = sortPrivatesByHeight2 (bubblePrivates height True lst)  (sum +sortingHelper lst 0)

sortingHelper :: [Private] -> Int -> Int
sortingHelper [] max =  max
sortingHelper [x] max = max
sortingHelper (x:y:xs) max
    | height x < height y = sortingHelper xs (maximum [timeToSwap x,timeToSwap y,max])
    | otherwise = sortingHelper (y:xs) max

--------------------------
-- Part II: Squeezing your Brain Muscles

--ceremonialFormation: Sorting again, but with multiple files. Don't forget the time!
ceremonialFormation :: Area -> (Area, Int)
ceremonialFormation area 
        [sortPrivatesByHeight a | a <- privlst]
    where
        privlst = [cellToPriv x | x <- area ]

cellToPriv :: [Cell] -> [Private]
cellToPriv [] = []
cellToPriv (x:xs)
    | x == Full Private = Private : cellToPriv xs
    | x == Empty = Private {0,0,0} : cellToPriv xs

privToCell :: [Private] -> [Cell] 
privToCell [] = []
privToCell (x:xs)
    | x == Private {0,0,0} = Empty : cellToPriv xs
    | otherwise Private x : privToCell xs
 

-- swapPrivates: Swap two arbitrary privates by ID if they are in the area. Big ouch!
swapPrivates :: Int -> Int -> Area -> Area
swapPrivates i1 i2 area = area 

-- Best of luck to you, friend and colleague!

