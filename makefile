all: bankingSystem

bankingSystem: bankingSystem.o
	gcc -fsanitize=address -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o: 
	gcc -fsanitize=address -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

bankingSystem.o: bankingSystem.c

clean:
	-rm bankingSystem.o bankingSystem
