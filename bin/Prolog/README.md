# Compile and Run
## Compile and Run
* Task 1: `swipl task1.pl`
## Example Run with Input
* Task 1: `echo '{"data":[{"id":1,"name":"Hoang","spread_radius":1,"movement_history":[[0,0],[1,1],[2,2]]},{"id":2,"name":"Quan","spread_radius":1,"movement_history":[[1,6],[1,8]]},{"id":3,"name":"something","spread_radius":3,"movement_history":[[1,2],[3,4],[5,6],[7,8]]}]}' | swipl task1.pl`
# Notes
* Task 1 uses standard input and standard output. If called by Python `subprocess.run`, be sure to set `stdin=PIPE, stdout=PIPE, input=json_str` (replace `json_str` with a string containing input json data, probably using `json.dumps(data)`)
