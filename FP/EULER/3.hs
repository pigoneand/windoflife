main = print answer
a = 600851475143
find_one_factor :: (Integral a) => a -> a
find_one_factor num = [x | x <- [2,3..num], num `mod` x == 0] !! 0
factors :: (Integral a) => a -> [a]
factors 1 = []
factors x = find_one_factor x : factors (x `div` (find_one_factor x))
answer = (reverse $ factors a) !! 0
