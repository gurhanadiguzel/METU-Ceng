module Sample where

fibonacci :: Int -> Int
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci n = fibonacci (n-1) + fibonacci (n-2)


fibonacci1 x
    | x== 0 =  0
    | x== 1 = 1
    | otherwise =  fibonacci (x-1) + fibonacci (x-2)


main :: IO()
main = putStrLn "HelloWorld!"