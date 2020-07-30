import json
from os import path, listdir, remove
from shutil import copy
import subprocess
from PIL import Image
import sys


class Task:
    def __init__(self, name, cmd):
        self.name = name
        self.cmd = cmd
        self.data = {}

    def run(self, *inps):
        # print('\n', self.name)
        if not path.exists(self.cmd) and path.exists(self.cmd + '.c'):
            subprocess.run(
                ['gcc', self.cmd + '.c', './bin/C/json-parser/json.c', '-o', self.cmd, '-lm', '-w'])
        if not path.exists(self.cmd) and path.exists(self.cmd + '.hs'):
            subprocess.run(['ghc', self.cmd + '.hs'])
        for inp in inps:
            with open('./temp/' + inp, 'r') as f:
                self.data.update(json.load(f))
            # print(type(self.data))
            # print(self.data)
        json_str = json.dumps(self.data)
        # print(json_str)
        p = subprocess.Popen(
            self.cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        with p.stdin:
            p.stdin.write(json_str.encode())
        output = p.stdout.read()
        with open('./temp/output' + self.name + '.json', 'w') as f:
            json.dump(json.loads(output), f)


# Function to draw pixel image of finished output
def draw():
    with open('./output.json') as f:
        d = json.load(f)
    matrix = d['spread_and_path_matrix']
    # print(matrix)
    width = len(matrix[0])
    height = len(matrix)
    image = Image.new('RGB', (width, height), 'white')
    pixels = image.load()
    for i in range(height):
        for j in range(width):
            # White for background
            color = (255, 255, 255)
            # Red for infected areas
            if matrix[i][j] == 1:
                color = (255, 0, 0)
            # Blue for path
            elif matrix[i][j] == 2:
                color = (0, 0, 255)
            pixels[j, i] = color
    image.save('./output.png')


# Process input
with open('input.json') as f:
    inp = json.load(f)
    for line, value in inp.items():
        # print(line, value)
        with open('./temp/' + line + '.json', 'w') as fi:
            json.dump(value, fi)
    # print(inp)

# Create task objects
# task1 = Task('1', 'echo')
task2 = Task('2', './bin/C/task2')
task3 = Task('3', './bin/C/task3')
task4 = Task('4', './bin/Haskell/task4')

# Run all task in sequence
# task1.run('input1.json')
task2.run('output1.json', 'input2.json')
task3.run('output2.json', 'input3.json')
task4.run('output3.json', 'output2.json')

# Output
copy('./temp/output4.json', './output.json')

# Delete temp files
# output1.json is kept because Task1 is not implemented
templist = [f for f in listdir('./temp/') if 'output1' not in f]
for f in templist:
    remove(path.join('./temp/', f))

# Draw pixel picture
draw()
