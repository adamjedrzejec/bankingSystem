all: bankingSystem

bankingSystem: bankingSystem.o operationsOnDatabase.o
	gcc -g $^ -o $@ -lm

.c.o:
	gcc -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

operationsOnDataBase.o: operationsOnDataBase.c operationsOnDatabase.h

bankingSystem.o: bankingSystem.c operationsOnDatabase.h

clean:
	-rm operationsOnDataBase.o bankingSystem.o bankingSystem
