import Data.Char
main = print answer
answer = sum $ map (digitToInt) (show $ 2^1000)
