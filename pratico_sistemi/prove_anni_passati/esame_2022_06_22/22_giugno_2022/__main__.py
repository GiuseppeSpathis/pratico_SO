import os
import sys
import subprocess


def print_file_info():
    
    directory = sys.argv[1]
    with os.scandir(directory) as entries:
        
        for entry in entries:
            print(entry.name)
            info = subprocess.run(['file', (directory + "/" + entry.name)], capture_output=True, text=True)
            print(info.stdout.split(':')[1].strip())

if __name__ == '__main__':
	print_file_info()