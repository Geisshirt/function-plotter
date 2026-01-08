#include <SDL2/SDL.h>
#include <stdio.h>
#include "tinyexpr/tinyexpr.h"
#include <math.h>

#define WIDTH 600
#define HEIGHT 600 

// Using Bresenham’s line algorithm https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm.
void draw_line(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 color) {
    Uint32 *pixels = (Uint32 *)s->pixels;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = 1;
    if (x0 >= x1) sx = -1; 
    int sy = 1;
    if (y0 >= y1) sy = -1;

    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        
        if (x0 >= 0 && x0 < s->w && y0 >= 0 && y0 < s->h) {
            pixels[y0 * s->w + x0] = color;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_grid(SDL_Surface *s, int x_min, int x_max, int y_min, int y_max) {
    Uint32 *pixels = (Uint32 *)s->pixels;
    Uint32 blue = SDL_MapRGB(s->format, 0, 0, 255);
    Uint32 gray = SDL_MapRGB(s->format, 190, 190, 190);
    Uint32 color = gray;

    // Vertical.
    for (int x = x_min; x <= x_max; x++) {
        int sx = (x - x_min) * (WIDTH-1) / (x_max - x_min);

        color = gray;
        if (x == 0) color = blue;

        for (int y = 0; y < HEIGHT; y++) {
            pixels[y * s->w + sx] = color;
        }
    }

    // Horizontal.
    for (int y = y_min; y <= y_max; y++) {
        int sy = (y_max - y) * (HEIGHT-1) / (y_max - y_min); // Seg faults without the -1 ??

        color = gray;    
        if (y == 0) color = blue;

        for (int x = 0; x < WIDTH; x++) {
            pixels[sy * s->w + x] = color;
        }
    }
}

void draw_function(SDL_Surface *s, int x_min, int x_max, int y_min, int y_max, te_expr *expr, double *x) {
    Uint32 red = SDL_MapRGB(s->format, 255, 0, 0);
    int prev_sx = 0;
    int prev_sy = 0;
    for (int sx = 0; sx < WIDTH; sx++) {
        *x = x_min + (double)sx * (x_max - x_min) / (WIDTH - 1);
        double y = te_eval(expr);

        int sy = (int)((y_max - y) * (HEIGHT - 1) / (y_max - y_min));

        draw_line(s, prev_sx, prev_sy, sx, sy, red);
        
        prev_sx = sx;
        prev_sy = sy;
    }
}

int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s exp x_min..x_max y_min..y_max\n", argv[0]);
        return 1;
    }

    // Parse the plot ranges.
    int x_min, x_max;    
    if (sscanf(argv[2], "%d..%d", &x_min, &x_max) != 2) {
        fprintf(stderr, "Invalid x range: %s\n", argv[2]);
        return 1;
    }

    int y_min, y_max;
    if (sscanf(argv[3], "%d..%d", &y_min, &y_max) != 2) {
        fprintf(stderr, "Invalid y range: %s\n", argv[3]);
        return 1;
    }

    // Parse the expression.
    double x;
    te_variable vars[] = {{"x", &x}};
    int err;
    te_expr *expr = te_compile(argv[1], vars, 1, &err);

    if (!expr) {
        printf("Parse error @ char %d\n", err);
        return 1;
    }

    // Setting up the window.
    SDL_Window *window = SDL_CreateWindow("Function Plotter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0); 
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    draw_grid(surface, x_min, x_max, y_min, y_max);
    draw_function(surface, x_min, x_max, y_min, y_max, expr, &x);

    te_free(expr);

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
