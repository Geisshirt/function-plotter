#include <SDL2/SDL.h>
#include <stdio.h>

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

