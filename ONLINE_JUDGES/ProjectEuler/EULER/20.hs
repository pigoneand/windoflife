import Data.Char
main = print answer
answer = sum $ map (digitToInt) $ show $ product [1..100]
