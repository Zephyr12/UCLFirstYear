isort :: (Ord a) => [a] -> [a]
isort [] = []
isort (x:xs) = insert x (isort xs)
    where insert x sorted = [y | y <- sorted, y <= x] ++ x : [y | y <- sorted, y > x]

merge :: (Ord a) => [a] -> [a] -> [a]
merge [] [] = []
merge x [] = x
merge [] y = y
merge (x:xs) (y:ys)
    | x < y = x : merge xs (y:ys)
    | x >= y = y : merge (x:xs) ys 

msort :: (Ord a) => [a] -> [a]
msort [] = []
msort [a] = [a]
msort xs = merge (msort $ take n xs) (msort $ drop n xs)
    where n = length xs `div` 2

rotor :: Int -> [a] -> [a]
rotor n xs = (drop n xs) ++ (take n xs)

makeKey :: Int -> [(Char, Char)]
makeKey n = zip ['A'..'Z'] (rotor n ['A'..'Z'])

lookUp :: Char -> [(Char, Char)] -> Char
lookUp c dict = case lookup c dict of
    Just v -> v
    Nothing -> c

encipher n c = lookUp c (makeKey n)

encrypted n = map (encipher n)
