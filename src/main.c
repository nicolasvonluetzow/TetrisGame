#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


/* main(...) // Apple/Windows */
#ifdef __APPLE__ /* Apple Macro */
int main(int argc, char **argv)
#elif defined __MINGW32__ /* Windows Macro */
int WinMain(int argc, char **argv) 
#endif

/* main(...) Anfang */
{
	if (SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER ) < 0)
	{
		printf("Fehler beim Initialisierungsprozesses von SDL: %s\n", SDL_GetError());
		return 1;
	}
		
	SDL_Window* win = SDL_CreateWindow("Tetris 1984", 
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										640, 480, 0);
	if (!win)
	{
		printf("Fehler beim Erstellen des Fensters: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	
	if (!rend)
	{
		printf("Fehler beim Initialisierungsprozesses des Renderers: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	SDL_Surface* sur = IMG_Load("ressources/hello.png");
	
	if (!sur)
	{
		printf("Fehler beim Initialisierungsprozesses von SDL: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(rend);
		SDL_Quit();
		return 1;
	}
	
	SDL_Delay(5000);
	
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return 0;
}