import Data.List

main = do 
    line <- getLine
    let heavyBits = getOccuranceBits line "heavy"
    let metalBits = getOccuranceBits line "metal"
    let heavyScan = scanl1 (+) (heavyBits)
    let answerScan = zipWith (*) heavyScan metalBits
    print (sum answerScan)

getOccuranceBits :: [Char] -> [Char] -> [Integer]
getOccuranceBits [] _ = []
getOccuranceBits (c:cs) (pattern) = now : (getOccuranceBits cs pattern) where
    now = if (isPrefixOf (pattern) (c:cs)) then 1 else 0


