#include <SDL2/SDL.h>


/* main(...) // Apple/Windows */
#ifdef __APPLE__ /* Apple Macro */
int main(int argc, char **argv)
#elif defined __MINGW32__ /* Windows Macro */
int WinMain(int argc, char **argv) 
#endif

/* main(...) Anfang */
{
	SDL_Init( SDL_INIT_EVERYTHING );
	
	SDL_Quit();
	
	return 0;
}