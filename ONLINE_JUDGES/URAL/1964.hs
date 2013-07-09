main = interact solve

york :: Integer -> Integer -> [Integer] -> Integer
york n now [] = now
york n now (x:xs) = if (now + x <= n) then 0 else york n (now + x - n) xs

solve :: String -> String
solve input = (show $ york n now a) ++ "\n" where
    args = map (read :: String -> Integer) $ words input
    n = args !! 0
    k = args !! 1
    now = args !! 2
    a = drop 3 args
