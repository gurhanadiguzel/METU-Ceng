
f :: Integer -> Integer
f x = x^2 + 3*x + 7

g :: Double -> Double -> Double
g x y = x * y + x

sumOfThree :: Int -> Int -> Int -> Int
sumOfThree a b c = a + b + c

isA :: Char -> Bool
isA c = c == 'a' || c == 'A'

commentOnGrade :: String -> String
commentOnGrade "AA" = "You rock, friend!"
commentOnGrade "BA" = "Ah, must have been bad luck!"
commentOnGrade other = "You missed the Haskell recitation, didnt you?"

fact :: Integer -> Integer
fact 0 = 1 -- base case, should be the first!
fact n = n * fact (n - 1) -- recursive case

trd :: (a, b, c) -> ((a, b, c), c)
trd triplet@(_, _, z) = (triplet, z) -- dont care about the first two


join :: String -> [String] -> String
join _ [] = "" -- empty list case, an empty string
join _ [str] = str -- single string case, only that string
join joinStr (firstStr:rest) = firstStr ++ joinStr ++ join joinStr rest


ifact :: Integer -> Integer
ifact n = if n == 0 then 1 else n * ifact (n - 1) -- one line


ifactChecked :: Integer -> Integer
ifactChecked n =    if n < 0 -- broken over multiple lines
                        then error "factorial of a negative value"
                        else ifact n


classify :: Double -> String
classify x
    | x < 1e-10 = "Thats tiny! Just like a pebble."
    | x < 1e-5 = "Almost negligible."
    | x < 1e5 = "A pretty normal value, if Ive ever seen one."
    | x < 1e10 = "Not bad, some pretty good stuff youve got there."
    | otherwise = "BigValue (TM)"


firstNLast :: String -> String
firstNLast fullName =   let nameList = words fullName -- splits on spaces
                            firstName = head nameList
                            lastName = last nameList
                        in [head firstName, '.',head lastName , '.']

-------------                      
firstNLast1 :: String -> String
firstNLast1 fullName = [head firstName1, '.', head lastName1,'.']
    where   nameList = words fullName -- splits on spaces
            firstName1 = head nameList
            lastName1 = last nameList
------------

luck :: [Int] -> Int
luck [] = 0
luck (x:xs) =   let luckIncrement = case x of   7 -> 1 -- lucky!
                                                13 -> -1 -- unlucky :(
                                                _ -> 0 -- who cares?
                in luckIncrement + luck xs