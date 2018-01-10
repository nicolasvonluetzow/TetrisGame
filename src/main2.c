#include <stdio.h>
#include <SDL2/SDL.h>

/* main(...) // Apple/Windows */
#ifdef __APPLE__ /* Apple Macro */
int main(int argc, char **argv)
#elif defined __MINGW32__ /* Windows Macro */
int WinMain(int argc, char **argv) 
#endif

{
	if (SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		printf("Fehler beim Initialisierungsprozesses von SDL: %s\n", SDL_GetError());
		return 1;
	}

	
	SDL_Quit();
	return 0;
}