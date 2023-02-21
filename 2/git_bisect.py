#!/usr/bin/env python3
import subprocess
import os
import sys

PATH = input('PATH: ')
start = input('FIRST COMMIT: ')
end = input('LAST COMMIT: ')
TEST_CMD = input('TEST COMMAND: ')

os.chdir(PATH)
commit_list = subprocess.run("git log --format='%H'", capture_output=True)\
                        .stdout.decode()\
                        .replace("'", '').strip('\n')\
                        .split('\n')[::-1]

left = commit_list.index(start)
right = commit_list.index(end)

while left <= right:
    mid = (left + right) // 2
    subprocess.run(f'git checkout {commit_list[mid]}')
    output = subprocess.run(TEST_CMD, capture_output=True).returncode
    if output != 0:
        subprocess.run(f'git checkout {commit_list[mid-1]}')
        if subprocess.run(TEST_CMD, capture_output=True).returncode == 0:
            print(f'Broken: {commit_list[mid-1]}')
            subprocess.run(f'git checkout {commit_list[-1]}')
            exit(0)
        else:
            right = mid - 1

    if output == 0:
        subprocess.run(f'git checkout {commit_list[mid + 1]}')
        if subprocess.run(TEST_CMD, capture_output=True).returncode != 0:
            print(f'Broken: {commit_list[mid+1]}')
            subprocess.run(f'git checkout {commit_list[-1]}')
            exit(0)
        else:
            left = mid + 1
