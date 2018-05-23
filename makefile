all: bankingSystem

bankingSystem: bankingSystem.o operationsOnDatabase.o
	gcc -g $^ -o $@ -lm

.c.o:
	gcc -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

operationsOnDatabase.o: operationsOnDatabase.c operationsOnDatabase.h

bankingSystem.o: bankingSystem.c operationsOnDatabase.h

clean:
	-rm operationsOnDatabase.o bankingSystem.o bankingSystem
