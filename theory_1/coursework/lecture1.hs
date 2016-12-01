safetail :: [a] -> [a]
safetail xs = if null xs then [] else tail xs

safeTail :: [a] -> [a]
safeTail xs
    | null xs  = []
    | otherwise = tail xs

stail :: [a] -> [a]
stail [] = []
stail xs = tail xs
