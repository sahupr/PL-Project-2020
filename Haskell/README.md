# Dependencies
* [aeson][https://hackage.haskell.org/package/aeson]
* [Data.ByteString.Lazy.UTF8][https://downloads.haskell.org/~ghc/6.12.1/docs/html/libraries/utf8-string-0.3.4/Data-ByteString-Lazy-UTF8.html]
# Compile and Run
## Compile
* Task 4: `ghc task4.hs`
* If linking error then try `ghc -dynamic task4.hs`
## Run
* Task 4: `./task4`
## Example Run with Input
* Task 4: `echo '{"spread_matrix":[[1,1,0,0,0,0,1,1,1,0],[1,1,1,0,0,1,1,1,1,1],[0,1,1,1,0,0,1,1,1,0],[0,0,1,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0]],"safe_path":[[0,2],[1,3],[2,4],[3,5],[3,6],[3,7],[3,8],[2,9]]}' | ./task4`
# Notes
* Task 4 uses standard input and standard output. If called by Python `subprocess.run`, be sure to set `stdin=PIPE, stdout=PIPE, input=json_str` (replace `json_str` with a string containing input json data, probably using `json.dumps(data)`)
