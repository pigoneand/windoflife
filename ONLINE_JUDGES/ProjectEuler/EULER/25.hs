fibs = 1 : 1 : (zipWith (+) fibs (tail fibs))
main = print ((length $ (takeWhile (<10^999) fibs)) + 1)
