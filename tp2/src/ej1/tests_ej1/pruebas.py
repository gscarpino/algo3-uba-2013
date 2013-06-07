from os import listdir, system
from os.path import isfile, join
import sys
from StringIO import StringIO
import re

if __name__ == '__main__':
	mypath = '.'
	output  = sys.argv[1]
	files = [ f for f in listdir(mypath) if isfile(join(mypath,f)) and re.match(output+'.*\.graph$', f) ]
	mo = re.match('([0-9 a-z A-Z ]+)', files[0])
	
	outputFile=open(output, 'w+')
	for arg in files :
		print arg
		
		inFile = open(arg)
		for line in inFile.readlines():			
			mo = re.match('^\s*?([0-9]+)\s*?([0-9]+)', line)

			string =  mo.group(1) + ' ' + mo.group(2)
			outputFile.write(string+'\n')
		
		
	outputFile.write('#')	
	outputFile.close()
		