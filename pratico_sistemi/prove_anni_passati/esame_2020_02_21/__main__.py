

import os
import sys
import subprocess

"""
    prendi come parametro una stringa in ascii
    stampa l'elenco dei file che contengono al loro interno la stringa passata come parametro, presenti nella directory 
    corrente e nelle sue sottodirectory, la lista deve essere ordinata in base al file modfiicato piu recentemente
"""

file_list = [] #e' un tupla di nome file-data di ultima modifica

def add_elements_to_list(dirpath):
    for current_dir, subdirs, files in os.walk(dirpath):
        for file in files:
            filename, file_extension = os.path.splitext(file)
            if file_extension == '': #il file e' un eseguibile
                return
            with open(os.path.join(current_dir, file), 'r') as rfile:
                file_list.append((rfile.name, len(file_extension))) 
            
         
if __name__ == '__main__':
   
    add_elements_to_list(sys.argv[1])
#key=lambda x: x[1] significa che bisogna fare il sorting solo sul secondo elemento, reverse significa che la sorta al contrario
    file_list = sorted(file_list, key =lambda x: x[1])
    print(file_list)
    
    
    