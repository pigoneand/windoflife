import MyOwnMath
import Data.Array

main = print answer 

primes = generatePrimes 30000

isabundant :: Int -> Bool
isabundant x = (sumOfDivisors x primes) > x + x
abundantMask = listArray (1, 30000) (map isabundant [1..30000])

isValid :: Int -> Int -> Bool
isValid x i = (abundantMask ! i) && (abundantMask ! (x - i))
isTwoAbundant x = or [ isValid x i | i <- [1..(x-1)], i <= x - i]
isTwoAbundantMask = listArray (1, 30000) (map isTwoAbundant [1..30000])

answer = sum $ [ x | x <- [1..30000], (isTwoAbundantMask ! x) == False ]
