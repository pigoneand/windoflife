import MyOwnMath

nums = map (\x -> x * (x + 1) `div` 2) [1, 2..]
primes = generatePrimes 1000000
answer = head [ x | x <- nums, numberFactors x primes > 500 ]
main = print answer
