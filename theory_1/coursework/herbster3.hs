import Data.List

next = (`mod` 31337) . (* 31334)

sln (seed:n:[]) = fmap (+1) (findIndex (\(x,y)->x==n) $ sortOn (\(x,y)->y) $ zip [1..n] $ take n $ iterate next seed)
