lengthOfChain x  
    | x == 1 = 1
    | (x `mod` 2) == 0 = (lengthOfChain (x `div` 2)) + 1
    | otherwise = (lengthOfChain (x * 3 + 1)) + 1

answer = snd $ maximum $ map (\x -> (lengthOfChain x, x)) [1,2..1000000]
main = print answer
