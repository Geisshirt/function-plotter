#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 600
#define HEIGHT 600 

void draw_point(SDL_Surface *s, int x, int y, int x_min, int x_max, int y_min, int y_max, Uint32 color) {
    int screen_x = (x - x_min) * WIDTH / (x_max - x_min);
    int screen_y = (y_max - y) * HEIGHT / (y_max - y_min);

    if (screen_x < 0 || screen_x >= WIDTH || screen_y < 0 || screen_y >= HEIGHT) return;

    Uint32 *pixels = (Uint32 *)s->pixels;
    pixels[screen_y * s->w + screen_x] = color;
}

void draw_grid(SDL_Surface *s, int x_min, int x_max, int y_min, int y_max) {
    Uint32 *pixels = (Uint32 *)s->pixels;
    Uint32 blue = SDL_MapRGB(s->format, 0, 0, 255);
    Uint32 gray = SDL_MapRGB(s->format, 190, 190, 190);
    Uint32 color = gray;

    // Vertical.
    for (int x = x_min; x <= x_max; x++) {
        int sx = (x - x_min) * WIDTH / (x_max - x_min);
        
        color = gray;
        if (x == 0) color = blue;

        for (int y = 0; y < HEIGHT; y++) {
            pixels[y * s->w + sx] = color;
        }
    }

    // Horizontal.
    for (int y = y_min; y <= y_max; y++) {
        int sy = (y_max - y) * HEIGHT / (y_max - y_min);

        color = gray;    
        if (y == 0) color = blue;

        for (int x = 0; x < WIDTH; x++) {
            pixels[sy * s->w + x] = color;
        }
    }
}

void draw_function() {

}

int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s x_min..x_max y_min..y_max\n", argv[0]);
        return 1;
    }

    // Parse the plot ranges.
    int x_min, x_max;    
    if (sscanf(argv[1], "%d..%d", &x_min, &x_max) != 2) {
        fprintf(stderr, "Invalid x range: %s\n", argv[1]);
        return 1;
    }
    
    int y_min, y_max;
    if (sscanf(argv[2], "%d..%d", &y_min, &y_max) != 2) {
        fprintf(stderr, "Invalid y range: %s\n", argv[2]);
        return 1;
    }

    // Parse the expression.
    // TODO:

    // Setting up the window.
    SDL_Window *window = SDL_CreateWindow("Function Plotter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0); 
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    draw_grid(surface, x_min, x_max, y_min, y_max);
    
    // Expression.

    // Show the window and wait for close.
    SDL_Event event;
    int running = 1;
    while (running) {
    	while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = 0;
            }
    	}
	    SDL_UpdateWindowSurface(window);
    }
}

