'''
Scrivere uno script o un programma python che corregga l'indentazione di tutti i file .c e .h presenti
nel sottoalbero della directory passata come parametro (la working directory se non vi sono
parametri).
Hint: il comando:
ex -n '+norm!gg=G' +wq prog.c
corrregge l'indentazione del programma sorgente C prog.c.
'''

import os
import sys
import subprocess


def fix(dirpath):
    
    with os.scandir(dirpath) as entries:
        for entry in entries:
            if entry.is_dir():
                os.chdir(dirpath + "/" + entry.name)
                fix(dirpath + "/" + entry.name)
            else:
                if((entry.name[-2:] == ".c") or (entry.name[-2:] == ".h")): #considero solo i file.c o file.h
                    #non so perche' questo comando usando vim vuole che lo runni con current working directory quella in cui e' presente
                    #il file quindi ogni volta ho dovuto cambiare la current working directory con os.chdir
                    subprocess.run(["vim", "-n", "+norm!gg=G", "+wq", entry.name], check=True) 
    
         
if __name__ == '__main__':
    
    if(len(sys.argv) < 2):     #non gli passi alcun argormento al main
        fix(os.getcwd())
    else:
        os.chdir(sys.argv[1]) 
        fix(sys.argv[1])
    