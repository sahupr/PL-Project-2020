import json
import subprocess


class Task:
    def __init__(self, name, cmd):
        self.name = name
        self.cmd = cmd

    def run(self, *inps):
        # print('\n', self.name)
        # for inp in inps:
        #     with open(inp, 'r') as f:
        #         if 'json' in inp:
        #             data = json.load(f)
        #         else:
        #             data = f.readlines()
        #     print(data)
        output = subprocess.run([self.cmd, self.name], shell=True,
                                capture_output=True, encoding='utf_8').stdout
        print(output)


task1 = Task('Task1', 'echo')
task2 = Task('Task2', 'echo')
task3 = Task('Task3', 'echo')
task4 = Task('Task4', 'echo')

task1.run('input1.json', 'input1.txt')
task2.run('output1.json', 'input2.txt')
task3.run('output2.txt', 'input3.txt')
task4.run('output3.json', 'output2.txt')
