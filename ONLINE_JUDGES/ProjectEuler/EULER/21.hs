import MyOwnMath
main = print (sum $ answer)
primes = generatePrimes 10000
isCare x = (sumOfDivisors y primes) == x + y && x /= y where
    y = (sumOfDivisors x primes) - x
answer = [ x | x <- [1..10000], isCare x ]
