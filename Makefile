CC = gcc
CFLAGS = `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

plot: main.c
	$(CC) -o plot main.c $(CFLAGS) $(LDFLAGS)

