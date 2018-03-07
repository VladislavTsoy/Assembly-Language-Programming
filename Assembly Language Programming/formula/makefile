all: formula

objects = formula.o nCr.o
headers = formula.h nCr.h

formula: formula.o nCr.o
	gcc -o formula formula.o nCr.o

formula.o: formula.c formula.h
	gcc -c formula.c formula.h
	
nCr.o: nCr.s nCr.h
	gcc -c nCr.s nCr.h
	
clean:
	-rm -f *.o
	-rm -f formula
	-rm -f *.h.gch
