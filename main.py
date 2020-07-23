import json
import os


class Task:
    def __init__(self, name, num):
        self.name = name
        self.num = num

    def run(self, *inps):
        print('\n', self.name)
        for inp in inps:
            with open(inp, 'r') as f:
                if 'json' in inp:
                    data = json.load(f)
                else:
                    data = f.readlines()
            print(data)
        if self.num == 1:
            # Insert command code to run task 1
            os.system('echo Task1')
        elif self.num == 2:
            # Insert command code to run task 2
            os.system('echo Task2')
        elif self.num == 3:
            # Insert command code to run task 3
            os.system('echo Task3')
        elif self.num == 4:
            # Insert command code to run task 4
            os.system('echo Task4')


task1 = Task('Task1', 1)
task2 = Task('Task2', 2)
task3 = Task('Task3', 3)
task4 = Task('Task4', 4)

task1.run('input1.json', 'input1.txt')
task2.run('output1.json', 'input2.txt')
task3.run('output2.txt', 'input3.txt')
task4.run('output3.json', 'output2.txt')
