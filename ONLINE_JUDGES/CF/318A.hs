main = interact (show . answer . readInput)

readInput :: String -> [Integer]
readInput line = (map read) . words $ line

answer :: [Integer] -> Integer
answer [n, k] = if (k <= (n + 1) `div` 2) then k * 2 - 1 else (k - (n + 1) `div` 2) * 2

