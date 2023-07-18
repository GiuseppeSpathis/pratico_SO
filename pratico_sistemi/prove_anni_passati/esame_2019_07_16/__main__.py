"""
Scrivere un programma python o uno script bash che cerchi tutti i file con uguale contenuto in una
directory. I file con lo stesso contenuto devono diventare link fisici a un unico file.
"""

import os
import sys
import subprocess

files = []

def getSameContent(contentOne):
        for file in files:
            with open(os.path.join(sys.argv[1], file), 'r') as f:
                content = f.read()
                if content == contentOne:
                    tmplist.append(file)                
                    files.remove(file)
            
def get_entries(dirpath):
    for current_dir, subdirs, files in os.walk(dirpath):
        return files
         
         
if __name__ == '__main__':
    files = get_entries(sys.argv[1])
    for file in files:
        tmplist = []
        with open(os.path.join(sys.argv[1], file), 'r') as f:
            files.remove(file)
            content = f.read()
            getSameContent(content)
            path = os.path.join(sys.argv[1], file)
            for file_ in tmplist:
                if file_ != file:
                    tmppath = os.path.join(sys.argv[1], file_)
                    os.unlink(tmppath)
                    os.link(path, tmppath)
  
    