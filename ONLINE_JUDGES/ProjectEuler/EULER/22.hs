import Data.List
import Data.Char

main = do
    content <- readFile "22.txt" 
    let inputwords = (read :: String -> [String]) ("[" ++ content ++ "]")
    let sortwords = sort inputwords
    let wordscores = zipWith (*) ([1..]) (map wordscore sortwords)
    print $ sum wordscores

wordscore :: String -> Int
wordscore s = sum $ map (\x -> (ord x) - (ord 'A') + 1) s
