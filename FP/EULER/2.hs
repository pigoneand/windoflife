main = print answer
fib = 1 : 1 : zipWith (+) fib (tail fib)
answer = sum [ x | x <- (takeWhile) (<= 4000000) fib, even x ]
