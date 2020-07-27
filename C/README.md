# Compile and Run
## Compile
Task 2: `gcc task2.c json-parser/json.c -o task2 -lm`\
Task 3: `gcc task3.c json-parser/json.c -o task3 -lm`
## Run
Task 2: `./task2`\
Task 3: `./task3`
## Example Run with Input
Task 2: `echo '{"geometric_shapes":[[1,0,0,1,1],[1,1,1,2,2],[1,1,6,1,8]],"sizex":10,"sizey":10}' | ./task2`\
Task 3: `echo '{"spread_matrix":[[1,1,0,0,0,0,1,1,1,0],[1,1,1,0,0,1,1,1,1,1],[0,1,1,1,0,0,1,1,1,0],[0,0,1,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0]],"startx":0,"starty":2,"endx":2,"endy":9}' | ./task3`
## Notes
* Task 2 and task 3 use standard input and standard output. If called by Python `subprocess.run`, be sure to set `stdin=PIPE, stdout=PIPE, input=json_str` (replace `json_str` with a string containing input json data, probably using `json.dumps(data)`)
