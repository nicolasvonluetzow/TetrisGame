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
										1280, 720, 0);
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
		printf("Fehler beim Initialisieren des Renderers: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	SDL_Surface* surface = IMG_Load("ressources/Tetris Background.jpg");
	
	if (!surface)
	{
		printf("Fehler beim Initialisieren der Oberflaeche: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	
	if (!tex)
	{
		printf("Fehler beim Erstellen der Textur: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, tex, NULL, NULL);
	SDL_RenderPresent(rend);
	
	SDL_Delay(5000);
	
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return 0;
}