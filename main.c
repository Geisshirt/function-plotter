#include <SDL2/SDL.h>
#include <stdio.h>

void plot(SDL_Surface *s) {
    Uint32 color = SDL_MapRGB(s->format, 255, 0, 0);
    for (int x = -300; x <= 300; x++) {

        // Move origin from top left to center.
	int centerX = 300 + x;
	int centerY = 300 - (x * x);

	if (centerX >= 0 && centerX <= 600 && centerY >= 0 && centerY <= 600) {
            ((Uint32 *)s->pixels)[centerY * 600 + centerX] = SDL_MapRGB(s->format, 255, 0, 0);
	}
    }
}

int main () {
    // Setting up the window.
    SDL_Window *window = SDL_CreateWindow("Function Plotter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0); 
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    // Grid.
    SDL_Rect xAxis = (SDL_Rect) {0, 300, 600, 2};
    SDL_FillRect(surface, &xAxis, 0x0000FF);
    SDL_Rect yAxis = (SDL_Rect) {300, 0, 2, 600};
    SDL_FillRect(surface, &yAxis, 0x0000FF);

    plot(surface);

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

