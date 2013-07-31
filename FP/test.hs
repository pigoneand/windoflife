import Data.Ratio
import Test.QuickCheck
import Data.List

quickSort [] = []
quickSort (x:xs) = (quickSort leftPart) ++ (x : (quickSort rightPart)) where 
    leftPart = filter (<x) xs
    rightPart = filter (>=x) xs

checkQuickSortResultStable x = (quickSort (quickSort x)) == (quickSort x)

main = verboseCheck (checkQuickSortResultStable :: [Integer] -> Bool)

