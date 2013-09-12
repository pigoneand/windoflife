main = interact (show. solve . (map read) . words)

solve :: [Integer] -> Integer
solve (a:b:n:c:d:m) = 1


