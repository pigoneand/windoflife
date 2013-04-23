is_palindrome :: Int -> Bool
is_palindrome x = (showx == reverse showx)
    where showx = show x
products = maximum [ x | a <- [100..999], b <- [100..999], let x = a * b, is_palindrome x]
main = print (products)
