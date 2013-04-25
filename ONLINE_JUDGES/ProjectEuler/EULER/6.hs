main = print answer
answer = (sum [1,2..100]) ^ 2 - (sum $ map (\x -> x * x) [1,2..100])
