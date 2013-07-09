import Data.List

main = print answer

data Dist a = Dist { unD :: [(a, Double)] } deriving (Show, Eq, Read)
type Event a = (a -> Bool)

-- get a uniform distribution from list of element
uniform :: [a] -> Dist a
uniform xs = Dist (map (\a -> (a, 1.0 / l)) xs) where 
    l = fromIntegral $ length xs

-- get event happen probability
getEventProb :: (Dist a) -> (Event a) -> Double
getEventProb d event = (sum . (map snd) . filter (event . fst) . unD $ d) / (sum . (map snd) . unD $ d)

-- normalize a distribution
normalize :: (Ord a, Eq a) => (Dist a) -> (Dist a)
normalize d = Dist [(x, getEventProb d (==x)) | x <- (nub . sort . map fst) $ unD d]

-- monad
instance Monad Dist where
    return x = Dist [(x, 1)] 
    (Dist d) >>= f = Dist [ (y, p * q) | (x, p) <- d, (y, q) <- unD (f x) ]

-- move function, transition function
move :: String -> Dist String
move "Head" = uniform ["Head", "Tail"]
move "Tail" = uniform ["Tail"]

-- example
move2 = uniform ["Head"] >>= move >>= move
answer = normalize move2


