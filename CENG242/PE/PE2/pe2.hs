module PE2 where

import Text.Printf

type Point = (Int, Int)
type Dimensions = (Int, Int)
type Vector = (Int, Int)

getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

castIntToDouble x = (fromIntegral x) :: Double

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------
getVector :: String -> Vector
getVector d = (x,y)
    where 
    (x,y)
        | d == "Stay" = (0,0)
        | d == "North" = (0,1)
        | d == "South" = (0,-1)      
        | d == "East" = (1,0)     
        | d == "West" = (-1,0) 
        | d == "NorthWest" = (-1,1)
        | d == "NorthEast" = (1,1)
        | d == "SouthWest" = (-1,-1)
        | d == "SouthEast" = (1,-1)

-------------------------------------------------------------------------------------------------------------------------------
getAllVectors :: [String] -> [Vector]
getAllVectors l = [ getVector(c) | c <- l ]

-------------------------------------------------------------------------------------------------------------------------------
producePath :: Point -> [String] -> [Point]
producePath (xi, yi) actions = (xi, yi) : producePath1 (xi, yi) actions
    
producePath1 :: Point -> [String] -> [Point]
producePath1 (xi, yi) (h:rest)
    |rest == [] =  [sum]
    |otherwise = [sum] ++ producePath1 sum rest
    where 
        sum = sumPoints (xi, yi) (getVector h)

sumPoints :: Point -> Point -> Point
sumPoints (x1,y1) (x2,y2) = (x1+x2, y1+y2)
-------------------------------------------------------------------------------------------------------------------------------
takePathInArea :: [Point] -> Dimensions -> [Point]
takePathInArea (headp:path) (bx, by)
    | xi>=0 && xi< bx && yi>=0 && yi< by = if path == [] then [(xi,yi)] else (xi,yi) : takePathInArea path (bx, by)
    | otherwise = []
    where 
        (xi,yi)  = headp

-------------------------------------------------------------------------------------------------------------------------------

remainingObjects :: [Point] -> Dimensions -> [Point] -> [Point]
remainingObjects path border objects = [x | x <- objects , (x`elem` takePathInArea path border) == False ]

-------------------------------------------------------------------------------------------------------------------------------
averageStepsInSuccess :: [[Point]] -> Dimensions -> [Point] -> Double
averageStepsInSuccess paths border objects = steps / len
    where 
        lst = [x | x <- paths, length x == length (takePathInArea x border) && length(remainingObjects x border objects) == 0]
        steps = castIntToDouble (sumSteps lst)
        len = castIntToDouble (length lst)
        
sumSteps :: [[Point]] -> Int
sumSteps (a:b)
    | b==[] = length a
    | otherwise = length a + sumSteps b   
