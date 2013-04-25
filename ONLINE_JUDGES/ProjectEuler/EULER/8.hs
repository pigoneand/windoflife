import Data.Char 
import Data.List 

main = do 
    str <- readFile "8.in"
    let numbers = map digitToInt ( concat $ lines str )
    let answer = maximum $ map (product . take 5) (tails numbers)
    print answer
