bankingSystem: bankingSystem.c
	gcc -fsanitize=address -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.PHONY: clean

clean:
	-rm bankingSystem
