import Data.List

main = print answer

answer = (sort $ permutations ['0'..'9']) !! 999999
