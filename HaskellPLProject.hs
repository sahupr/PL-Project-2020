--max3 :: (Double, Double, Double) -> Double
--max3 (x, y, z) = max (max x y) z
traverseTemp :: ([Integer], Integer, Integer, Integer) -> [Integer]
traverseTemp (temp, x, y, i) = 
	if i == y
		then num = temp !! pathY
	

matrixPath :: ([[Integer]], [[Integer]], Integer, Integer, [[Integer]]) -> [[Integer]])
matrixPath (matrix, path, i, ix, output) = 
	temp = matrix !! i
	pathX = path !! ix !! 0
	pathY = path !! ix !! 1
	if pathX == i
		then temp = traverseTemp (temp, pathX, pathY, 0)
			output = output ++ temp
	if i > length path
		then print output
	else matrixPath (matrix, path, i+1, ix+1, output)
		
	