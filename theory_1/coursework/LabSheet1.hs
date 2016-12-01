import Data.Char


square :: (Num a) => a -> a
square x = x * x

pyth :: (Num a) => a -> a -> a
pyth a b = square a + square b

isTriple :: (Num a, Eq a) => a -> a -> a -> Bool
isTriple a b c = pyth a b == square c


isTripleAny :: (Num a, Eq a) => a -> a -> a -> Bool
isTripleAny a b c = isTriple a b c || isTriple a c b || isTriple c b a

halfEvens :: (Integral a) => [a] -> [a]
halfEvens xs = [if x `mod` 2 == 0 then x `div` 2 else x | x <- xs]

inRange :: (Ord a) => a -> a -> [a] -> [a]
inRange min max = filter (\x -> x > min && x < max)

countPositives :: [Int] -> Int
countPositives xs = length $ filter (> 0) xs

capitalised :: [Char] -> [Char]
capitalised (x:xs) = (toUpper x) :  (map toLower xs)

title :: [String] -> [String]
title (first:words) = capitalised first : [if length x < 4 then lower x else capitalised x | x <- words ]
    where lower = map toLower
