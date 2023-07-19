"""Scrivere un programma python o uno script bash che faccia l'elenco dei pathname in un sottoalbero
che sono link fisici fra loro:
e.g.
searchln mydir
mydir/a mydir/d/b mydir/qq
mydir/uno mydir/due
significa che i path mydir/a mydir/d/b mydir/qq fanno riferimento allo stesso file, cosi' come mydir/uno
mydir/due indicano uno stesso file (diverso dal precedente).
Nel sottoalbero possono esserci molteplici altri file, se hanno un solo nome non vengono indicati
nell'output
"""


"""
l'idea e' che visito la directory e appena trovo un hard link lo metto metto nella lista degli hard link e poi con
la funzione hard_link dalla lista che ho creato, creo una matrice che in ogni riga ha tutti gli hard link associati che puntano allo stesso file
"""
import os, sys
import numpy as np

matrix = [] 


def calculate_matrix(dirpath):
    global matrix
    for current_dir, subdirs, files in os.walk(dirpath):
        for file in files:  #file e' il nome del file senza il path
            matrix = matrix + create_small_matrix(file)

def create_small_matrix(file):
    with open(os.path.join(sys.argv[1], file), 'r') as f:
        lines = f.readlines()
        numpy.zeros()
        for line in lines:
            row = []
            row.append(len(line.strip())) # Aggiungi il numero di caratteri della riga alla matrice
            matrix.append(row)
        return matrix

         
if __name__ == '__main__':
    calculate_matrix(sys.argv[1])
    print(matrix)