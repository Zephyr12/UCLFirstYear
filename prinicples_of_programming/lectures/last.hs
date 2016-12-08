total f = (\x-> foldr (+) 0 $ map f [1..x])
fl f = (\x y->f y x)

curry :: ((a, b) -> c) -> a -> b -> c
curry f = (\x y -> f (x,y))
