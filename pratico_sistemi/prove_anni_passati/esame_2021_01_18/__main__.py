

import os
import sys
import subprocess

"""
    prendi come parametro una stringa in ascii
    stampa l'elenco dei file che contengono al loro interno la stringa passata come parametro, presenti nella directory 
    corrente e nelle sue sottodirectory, la lista deve essere ordinata in base al file modfiicato piu recentemente
"""

file_list = [] #e' un tupla di nome file-data di ultima modifica
search_string = ""

def add_elements_to_list(dirpath):
    for current_dir, subdirs, files in os.walk(dirpath):
        for file in files:
            with open(os.path.join(current_dir, file), 'r') as rfile:
                if ((rfile.name[-2:] == ".c") or (rfile.name[-2:] == ".h") or (rfile.name[-4:] == ".txt")):
                    content = rfile.read()
                    if search_string in content:
                        # Aggiungi il nome del file alla lista
                        file_list.append((rfile.name, os.path.getmtime(rfile.name))) 
            
         
if __name__ == '__main__':
    dirpath = os.getcwd()
    search_string = sys.argv[1]
    add_elements_to_list(dirpath)
#key=lambda x: x[1] significa che bisogna fare il sorting solo sul secondo elemento, reverse significa che la sorta al contrario
    file_list = sorted(file_list, key =lambda x: x[1], reverse = True)
    print(file_list)
    
    
    