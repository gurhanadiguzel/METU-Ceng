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
    |sortPrivatesHelper lst 0 == 0 = (lst, sum)
    |otherwise = sortPrivatesByHeight2 (bubblePrivates height True lst)  (sum +sortPrivatesHelper lst 0)

sortPrivatesHelper :: [Private] -> Int -> Int
sortPrivatesHelper [] max =  max
sortPrivatesHelper [x] max = max
sortPrivatesHelper (x:y:xs) max
    | height x < height y = sortPrivatesHelper xs (maximum [timeToSwap x,timeToSwap y,max])
    | otherwise = sortPrivatesHelper (y:xs) max

--------------------------
-- Part II: Squeezing your Brain Muscles
isEmpty :: Cell-> Private
isEmpty Empty = Private 0 0 0
isEmpty (Full a) = a 

cellToPriv ::  [Cell]->[Private]  
cellToPriv [] = []
cellToPriv (x:xs)=  isEmpty x : cellToPriv xs

privToCell :: [Private] -> [Cell] 
privToCell [] = []
privToCell (x:xs)
    | height x ==  0  = Empty : privToCell xs
    | otherwise = Full x : privToCell xs
    
helper :: [(a, b)] -> [a]
helper tpllst = [fst b | b<- tpllst]
helper2 :: [(a1, a2)] -> [a2]
helper2 tpllst = [snd b | b<- tpllst]
    
--ceremonialFormation: Sorting again, but with multiple files. Don't forget the time!
ceremonialFormation :: Area -> (Area, Int)
ceremonialFormation area = (lArea,summation)
    where
        privlst = [cellToPriv x | x <- area]        
        lArea= let a3 = helper [sortPrivatesByHeight a| a <- privlst] in [privToCell x | x<-a3]
        summation=maximum (helper2 [sortPrivatesByHeight a| a <- privlst])

-- swapPrivates: Swap two arbitrary privates by ID if they are in the area. Big ouch!
swapPrivates :: Int -> Int -> Area -> Area
swapPrivates i1 i2 area = area