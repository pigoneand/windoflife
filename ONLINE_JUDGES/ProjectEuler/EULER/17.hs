one = ["one","two","three","four","five","six","seven","eight",
    "nine","ten","eleven","twelve","thirteen","fourteen","fifteen",
    "sixteen","seventeen","eighteen", "nineteen"]
ty = ["twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"]

solve 0 = 0
solve x
    | x < 20                                        = length $ (one !! (x - 1))
    | x < 100 && (x `mod` 10 == 0)                  = length $ (ty !! (x `div` 10 - 2))
    | x < 1000 && (x `mod` 100 == 0)                = 7 + solve (x `div` 100)
    | x == 1000                                     = 3 + 8
    | x > 100                                       = 3 + 7 + solve (x `div` 100) + solve (x `mod` 100)
    | otherwise                                     = solve (x `mod` 10) + solve (x `div` 10 * 10)

main = print ( sum $ map solve [1,2..1000])

