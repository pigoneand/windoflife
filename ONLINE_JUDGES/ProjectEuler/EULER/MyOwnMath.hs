module MyOwnMath where
import Data.List

-- ordered lists, difference and union
orderedminus (x:xs) (y:ys) = case (compare x y) of 
    LT -> x : orderedminus  xs  (y:ys)
    EQ ->     orderedminus  xs     ys 
    GT ->     orderedminus (x:xs)  ys
orderedminus  xs     _     = xs

orderedunion (x:xs) (y:ys) = case (compare x y) of 
    LT -> x : orderedunion  xs  (y:ys)
    EQ -> x : orderedunion  xs     ys 
    GT -> y : orderedunion (x:xs)  ys
orderedunion  xs     []    = xs
orderedunion  []     ys    = ys

-- generate primes from 2 to m
generatePrimes m = 2 : sieve [3,5..m]  where
    sieve [] = []
    sieve (p:xs) 
        | p*p > m   = p : xs
        | otherwise = p : sieve (xs `orderedminus` [p*p, p*p+2*p..])

-- generate prime factors of x, using second parameter as known primes
primeFactors x [] = [x]
primeFactors 1 _ = []
primeFactors x (p:ps) 
    | x `mod` p == 0    = p : primeFactors (x `div` p) (p:ps)
    | otherwise         = primeFactors x ps

-- calculate number of divisors in given number
numberOfDivisors 1 _  = 1
numberOfDivisors x ps = product $ map (( \x -> x + 1 ) . length) $ group $ primeFactors x ps

-- calculate sum of divisors of given number, include the number it self
divisorsHelper x = (p ^ (l + 1) - 1) `div` (p - 1) where
    p = x !! 0
    l = length x
sumOfDivisors 1 _ = 1
sumOfDivisors 0 _ = 0
sumOfDivisors x ps = (product $ map (divisorsHelper) $ group $ primeFactors x ps)
