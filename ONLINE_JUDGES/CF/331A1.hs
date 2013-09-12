import qualified Data.Map as Map

main = interact ( output . solve . input )

input :: String -> [Int]
input x = (map read) (words x)

infinite = 1000000000 * 1000000000

solve :: [Int] -> (Int, [Int])
solve x = (ans, [2]) where
    rightMostMap = Map.insert 1 1 Map.empty

    ans = rightMostMap (Map.!) 4

    --cal curL = if (curL == curR) then -1 * infinite else sumLR where
    --    curNumber = initArray ! curL 
    --    curR = (rightMostMap ! curNumber)
    --    sumLR = (sumArray ! (curR)) - (sumArray ! (curL - 1)) + delta
    --    delta = if (curNumber < 0) then 2 * curNumber else 0 


output :: (Int, [Int]) -> String
output (a, b) = (show a) ++ " " ++ (show (length b)) ++ "\n" ++ (concat (map (++ " ") (map show b)))
