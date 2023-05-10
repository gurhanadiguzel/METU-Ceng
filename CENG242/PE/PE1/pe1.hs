module PE1 where

import Text.Printf
import Data.List

-- Type synonyms --
type Point = (Double, Double)
type Signal = (Double, Double, Double, Double)

-- This function takes a Double and rounds it to 2 decimal places as requested in the PE --
getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

getDistance :: Point -> Point -> Double
getDistance (x1, y1) (x2, y2) = getRounded(sqrt((x1-x2)* (x1-x2)+ (y1-y2)*(y1-y2)))

-------------------------------------------------------------------------------------------

findAllDistances :: Point -> [Point] -> [Double]
findAllDistances b l = [getDistance b x | x <- l] 

-------------------------------------------------------------------------------------------

findExtremes :: Point -> [Point] -> (Point, Point)
findExtremes b l = 
            (head [x | x<- l, min == getDistance b x],head [x | x<- l, max == getDistance b x]) 
        where 
            min = minimum[a | a<- findAllDistances b l]
            max = maximum[y | y<- findAllDistances b l]

-------------------------------------------------------------------------------------------

getSingleAction :: Signal -> String
getSingleAction (b1,a1,b2,a2) = lastString
    where
    a 
        | b2<b1 = "North"
        | b1<b2 = "South"
        |otherwise  =""
    b
        | a2<a1 = "East"
        | a1<a2 = "West"
        |otherwise = ""
    lastString
        | a++b == "" = "Stay"
        |otherwise = a++b

-------------------------------------------------------------------------------------------

getAllActions :: [Signal] -> [String]
getAllActions signals = [getSingleAction x| x<-signals]

-------------------------------------------------------------------------------------------

numberOfGivenAction :: Num a => [Signal] -> String -> a
numberOfGivenAction signals action = c
    where
        c = fromIntegral (length [x | x <- getAllActions signals , action ==x])