main = print answer
answer = [ x | a <- [1..1000], b <- [1..1000], c <- [1..1000], a * a + b * b == c * c, a + b + c == 1000, let x = a * b * c] !! 0
