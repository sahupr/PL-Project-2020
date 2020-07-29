{-# LANGUAGE DeriveGeneric  #-}
{-# LANGUAGE DeriveAnyClass #-}

import qualified GHC.Generics as Generics
import qualified Data.Aeson as Aeson
import qualified Data.ByteString.Lazy as BL
import qualified Data.ByteString.Lazy.UTF8 as BLU
import qualified Data.List as List

data InputData = InputData
    { spread_matrix :: [[Int]]
    , safe_path :: [[Int]]
    }
    deriving (Show, Generics.Generic, Aeson.FromJSON)

data OutputData = OutputData
    { spread_and_path_matrix :: [[Int]]
    }
    deriving (Show, Generics.Generic, Aeson.ToJSON)

sortPredicate :: [Int] -> [Int] -> Ordering
sortPredicate [a, b] [c, d] =
    if a < c
        then LT
        else if a > c
            then GT
            else if b < d
                then LT
                else if b > d
                    then GT
                    else EQ

recursiveBuildMatrix :: [[Int]] -> [[Int]] -> Int -> Int -> [[Int]]
recursiveBuildMatrix [] safePath x y = []
recursiveBuildMatrix (spreadMatrixHead:spreadMatrixTail) safePath x y =
    if not (null safePath) && (head (head safePath) < x)
        then recursiveBuildMatrix (spreadMatrixHead:spreadMatrixTail) (tail safePath) x y
        else (recursiveBuildRow spreadMatrixHead safePath x y) : (recursiveBuildMatrix spreadMatrixTail safePath (x + 1) y)

recursiveBuildRow :: [Int] -> [[Int]] -> Int -> Int -> [Int]
recursiveBuildRow [] safePath x y = []
recursiveBuildRow (spreadRowHead:spreadRowTail) safePath x y =
    if not (null safePath) && (last (head safePath) < y)
        then recursiveBuildRow (spreadRowHead:spreadRowTail) (tail safePath) x y
        else if not (null safePath) && (head (head safePath) == x) && (last (head safePath) == y)
            then 2 : recursiveBuildRow spreadRowTail (tail safePath) x (y + 1)
            else spreadRowHead : recursiveBuildRow spreadRowTail safePath x (y + 1)

toInputByteString :: [Char] -> BL.ByteString
toInputByteString inputJsonString = BLU.fromString inputJsonString

toMaybeInputData :: BL.ByteString -> Maybe InputData
toMaybeInputData inputByteString = Aeson.decode inputByteString

toInputData :: Maybe InputData -> InputData
toInputData maybeInputData = case maybeInputData of
    Just value -> value
    Nothing -> InputData [] []

toSpreadAndPathMatrix :: InputData -> [[Int]]
toSpreadAndPathMatrix inputData = recursiveBuildMatrix (spread_matrix inputData) (List.sortBy sortPredicate (safe_path inputData)) 0 0

toOutputData :: [[Int]] -> OutputData
toOutputData spreadAndPathMatrix = OutputData spreadAndPathMatrix

toOutputByteString :: OutputData -> BL.ByteString
toOutputByteString outputData = Aeson.encode outputData

toOutputJsonString :: BL.ByteString -> [Char]
toOutputJsonString outputByteString = BLU.toString outputByteString

main :: IO ()
main = do
    inputJsonString <- getContents
    putStrLn $ toOutputJsonString $ toOutputByteString $ toOutputData $ toSpreadAndPathMatrix $ toInputData $ toMaybeInputData $ toInputByteString $ inputJsonString