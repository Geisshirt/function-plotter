CC = gcc
FLAGS = `sdl2-config --cflags` `sdl2-config --libs` tinyexpr/tinyexpr.c -lSDL2 -lm

all: main.c
	$(CC) -o plot main.c $(FLAGS)

clean:
	-rm plot
