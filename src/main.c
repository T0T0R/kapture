#include <stdio.h>

#include <SDL2/SDL.h>

#include "settings.h"
#include "world.h"
#include "events.h"

int main(int argc, char** argv)
{
	// Initializing world
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL2\n%s\n", SDL_GetError());
		return -1;
	}

	// Creating the window
	SDL_Window* window = SDL_CreateWindow("Kapture", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGTH, SDL_WINDOW_SHOWN);
	if(!window)
	{
		fprintf(stderr, "Failed to create the window\n%s\n", SDL_GetError());
		return -1;
	}

	// Creating renderer
	// TODO use hardware acceleration	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_UpdateWindowSurface(window);
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	// Initialize world
	WorldResources worldResources;
	worldResources.selectedPawn = NULL;
	setupWorld(renderer, &worldResources);

	// Main game loop
	int shouldClose = 0;
	SDL_Event event;
	while(!shouldClose)
	{
		while(SDL_PollEvent(&event))
		{
			shouldClose = handleEvent(event, &worldResources);
		}

		SDL_UpdateWindowSurface(window);
		
		SDL_RenderClear(renderer);

		renderWorld(renderer, &worldResources);
		
		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_DestroyWindow(window);
	
	return 0;
}
