main = print answer

answer = f (5, 95)

-- (red eyes, blue eyes), number of turns to let red eyes recognize their situation
f :: (Int, Int) -> Int 
f (0, _) = 0
f (r, b) = (f ((r - 1, b + 1)))  + 1
