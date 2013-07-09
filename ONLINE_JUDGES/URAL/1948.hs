import Data.Ratio
main = interact (output . (map solve) . readInput)
--main = print (squareSumOdd 3)

squareSum :: Integer -> Ratio Integer
squareSum x = x * (x + 1) * (x + x + 1) % 6

squareSumOdd :: Integer -> Ratio Integer
squareSumOdd x = (squareSum (x * 2)) - (squareSum x) * 4

solve :: (Integer, Integer, Integer)  -> Integer
solve (a, b, c) = if (delta == 0) then 2 else if (delta < 0) then 1 else ret where
    delta = b * b - 4 * a * c
    rcoff x = (x * delta) % (a * a * 4)
    lcoff 1 = 0
    lcoff x = if (odd x) then 2 * squareSum (x `div` 2) else (squareSumOdd (x `div` 2)) / 2
    isok x = (lcoff x) > (rcoff x)

    binarySearch l r = if (l == r) then l else if (isok mid) then binarySearch l mid else binarySearch (mid + 1) r where
        mid = (l + r) `div` 2
    ret = binarySearch 2 1000000000000000000

output :: [Integer] -> String
output ans = concat $ (map (\x -> x ++ "\n")) $ (map (show) ans)

readInput :: String -> [(Integer, Integer, Integer)]
readInput input = groupBy3 $ (map (read :: String -> Integer) (tail $ words $ input))

groupBy3 :: [Integer] -> [(Integer, Integer, Integer)]
groupBy3 (a:b:c:xs) = (a, b, c) : (groupBy3 xs)
groupBy3 _ = []
