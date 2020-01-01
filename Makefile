all: snake
snake: snake.o 
		gcc snake.c -o snake  -lncurses -lm
snake.o: snake.c
		gcc -c snake.c
clean:
		rm -f snake.o
		rm -f snake 
.PHONY: clean
