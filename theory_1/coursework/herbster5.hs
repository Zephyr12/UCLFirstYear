import Data.List

-- data Graph a = Node a [Graph a]

graphContains target (Node a as) = (a == target) || any id (map (graphContains target) as)

intToCoord i = ((i-1) `mod` 4, (i-1) `div` 4)

clamp mn mx = max mn.min mx

addT (x,y) (a,b) = (x+a, b+y)

sanitize x = clamp 0 3 x

sanitizeT (x,y) = (sanitize x, sanitize y)

coordToInt (x,y) = x + 4*y + 1

adj n = nub $ map (\x->coordToInt$sanitizeT$addT x (intToCoord n)) [(0,0), (0,1), (1,0), (-1,0),(0,-1)]

whack moles n = map (\(i,x)-> if i `elem` adj n then not x else x) (zip [1..] moles)

-- solve lst = bfs (Node lst []) whack (take 16 $ repeat [False])
