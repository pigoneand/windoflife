main = do
    content <- getContents
    print (answer content)

answer input = take 10 $ show $ sum $ map (read :: String -> Integer) (lines input)
