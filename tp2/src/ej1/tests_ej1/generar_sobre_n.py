from os import listdir, system
from os.path import isfile, join
import re
import sys
import math

def digrafo(nodos, aristas, salida):
	return '2 '+ str(nodos) + ' ' + str(aristas) + ' ' + '1' + ' ' + '1' + ' '\
	+ salida +'_'+ str(nodos).zfill(5)  +'_'+ str(aristas) + '.graph' + ' 0' 
	
def dag(nodos, aristas, salida):
	return '4 '+ str(nodos) + ' ' + str(aristas) + ' ' + '1' + ' ' \
	+ salida +'_'+ str(nodos).zfill(5)  +'_'+ str(aristas) + '.graph' + ' ' \
	+ 'ts.txt 0'
						
if __name__ == '__main__':
	mypath = '.'
	
	#1000 nodos, 1000 aristas, cambia c cantidad componetnes conexas
	output  = sys.argv[1]
	tipo = sys.argv[2]
	n = int(sys.argv[3])
	m = int(sys.argv[4]	)
	
	for t in range(1, n):
	#generamos entrada para el algoritmo
		input = open('input_'+output , 'w+');
		if(tipo == 'dag'):
			input.write(dag(t, m, output))
		if(tipo == 'dig'):
			input.write(digrafo(t, m, output))
		input.close()
		#generamos un grafo con la entrada anterior
		system("generador.exe " + ' < input_'+output)

		
	system("pruebas.py " +   output)