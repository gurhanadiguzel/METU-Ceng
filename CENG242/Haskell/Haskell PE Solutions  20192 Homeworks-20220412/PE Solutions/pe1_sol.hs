module PE1 where

import Text.Printf
import Data.List

type Point = (Double, Double)
type Signal = (Double, Double, Double, Double)

getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

----------------------------------------------------------------------------------------------------------------------
getDistance :: Point -> Point -> Double
getDistance (x1, y1) (x2, y2) = getRounded $ sqrt $ d_x^2 + d_y^2
                               where d_x = abs $ x1 - x2
                                     d_y = abs $ y1 - y2

----------------------------------------------------------------------------------------------------------------------
findAllDistances :: Point -> [Point] -> [Double]
findAllDistances b l = [getDistance p b | p <- l]
----------------------------------------------------------------------------------------------------------------------
eliminateJust Nothing = -1      -- code never reaches here, just for the complete definition.
eliminateJust (Just x) = x      -- to get index values as Int from "Just Int".

getMinIndex l = eliminateJust $ elemIndex (foldl1' min l) l         -- foldl1' is a higher order reduction function that sets the initial value as the first element
getMaxIndex l = eliminateJust $ elemIndex (foldl1' max l) l

findExtremes :: Point -> [Point] -> (Point, Point)
findExtremes b l = (nearest, farthest)
                   where distances = findAllDistances b l
                         nearest = l !! (getMinIndex distances)
                         farthest = l !! (getMaxIndex distances)
----------------------------------------------------------------------------------------------------------------------

-- this may look like a overkill, but I prefer encrypting the signal in order to avoid nested conditions
getDirectionEncryptHelper (n,e,s,w) "North" = if n - s > 0 then "1" else "0"
getDirectionEncryptHelper (n,e,s,w) "East" = if e - w > 0 then "1" else "0"
getDirectionEncryptHelper (n,e,s,w) "South" = if s - n > 0 then "1" else "0"
getDirectionEncryptHelper (n,e,s,w) "West" = if w - e > 0 then "1" else "0"

getDirectionEncrypt signal = intercalate "" $ [getDirectionEncryptHelper signal d | d <- alldirections] -- intercalate flattens a given nested list by putting the first argument between every elements. in this case, it joins the strings in the list.
                            where alldirections = ["North", "East", "South", "West"]

getSingleAction :: Signal -> String
getSingleAction signal = case encrypt of "0000" -> "Stay"
                                         "1000" -> "North"
                                         "0010" -> "South"
                                         "0001" -> "West"
                                         "1001" -> "NorthWest"
                                         "0011" -> "SouthWest"
                                         "0100" -> "East"
                                         "1100" -> "NorthEast"
                                         "0110" -> "SouthEast"
                         where encrypt = getDirectionEncrypt signal

-- alternative and more readable solution from Yusuf Celik
getSingleAction' :: Signal -> String
getSingleAction' (n, e, s, w) = result
         where x = e - w
               y = n - s
               vertical = if y == 0 then "" else
                         if y > 0 then "North" else "South"
               hortical = if x == 0 then "" else
                         if x > 0 then "East" else "West"
               direction = vertical ++ horizontal
               result = if direction == "" then "Stay" else direction
----------------------------------------------------------------------------------------------------------------------
getAllActions :: [Signal] -> [String]
getAllActions signals = [getSingleAction s | s <- signals]
----------------------------------------------------------------------------------------------------------------------
numberOfGivenAction :: Num a => [Signal] -> String -> a
numberOfGivenAction signals action = sum [1 | a <- actions, a == action]        -- alternative way to count while filtering the actions
                                   where actions = getAllActions signals
