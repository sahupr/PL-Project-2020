
replace pos newVal list = take pos list ++ newVal : drop (pos+1) list

matrixPath :: ([[Int]], [[Int]], Int, Int, [[Int]]) -> [[Int]]
matrixPath (matrix, path, i, ix, [[]]) = 
    if i == length path
	    then [[]]
	else
        if (path !! ix !! 0) == i	
            then matrixPath(matrix, path, i+1, ix + 1, ([replace (path !! ix !! 1) 2 (matrix !! i)]))
        else
			matrixPath (matrix, path, i+1, ix, ([matrix !! i]))
matrixPath (matrix, path, i, ix, output) = 
	if ix == length path
	    then if i == length matrix
		        then output
			else 
			    matrixPath(matrix,path,i+1,ix,(output ++ [matrix !! i]))
	else
        if (path !! ix !! 0) == i	
            then matrixPath(matrix, path, i+1, ix + 1, (output ++ [replace (path !! ix !! 1) 2 (matrix !! i)]))
        else
			matrixPath (matrix, path, i+1, ix, (output ++ [matrix !! i]))
