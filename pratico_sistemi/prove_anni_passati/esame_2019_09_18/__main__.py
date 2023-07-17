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

hard_links = [] #tupla nome file, inode


def find_hard_links(dirpath):
    for current_dir, subdirs, files in os.walk(dirpath):
        
        for file in files:  #file e' il nome del file senza il path
            stat_info = os.stat(file)
            # controlla se il numero di link è maggiore di 1
            if stat_info.st_nlink > 1: #e' un hard link
                hard_links.append((file, stat_info.st_ino)) 

def hard_link(links_list, inode): 
    global hard_links #global serve a indicare a filter che hard_links =  non e' una lista locale ma si riferisce alla lista globale
    for element in hard_links:
        if inode == element[1]:
            links_list.append(element[0])
            #questo filtro sostanzialmente serve a rimuovere l'elemento dalla lista, se usavo il semplice remove non funzionava essendo una lista di tuple
            hard_links = list(filter(lambda x: x[0] != element[0], hard_links)) 
            

         
if __name__ == '__main__':
    find_hard_links(sys.argv[1])
    for element in hard_links:
        tmplist = []
        hard_link(tmplist, element[1])
        if(len(tmplist) > 0):
            print(tmplist)