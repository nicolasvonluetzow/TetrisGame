#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720
#define FPS 60

// Geschwindigkeit ueber den Bildschirm in Pixel/Sekunde
#define SPEED 300

/* main(...) // Apple/Windows */
#ifdef __APPLE__ /* Apple Macro */
int main(int argc, char **argv)
#elif defined __MINGW32__ /* Windows Macro */
int WinMain(int argc, char **argv) 
#endif

/* main(...) Anfang */
{
	
	
	
	/* Anfang Basic Framework */
	if (SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER ) < 0)
	{
		printf("Fehler beim Initialisierungsprozesses von SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Tetris 1984", 
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										RESOLUTION_WIDTH, 
										RESOLUTION_HEIGHT, 0);
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
	/* Ende Basic Framework */
	
	
	
	//Struct der Position und Groesse des Sprites
	SDL_Rect dest;
	
	//Dimension der Textur
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
	dest.w /= 2;
	dest.h /= 2;
	
	// Starte Sprite in der Mitte des Fensters
	float x_pos = (RESOLUTION_WIDTH - dest.w) / 2;
	float y_pos = (RESOLUTION_HEIGHT - dest.h) / 2;
	float x_vel = 0;
	float y_vel = 0;
	
/*	//Positioniere das Sprite an der unteren Mitte des Fensters
	dest.x = (RESOLUTION_WIDTH - dest.w) / 2;
	
	// float Resolution fuer die y- Position
	float y_pos = RESOLUTION_HEIGHT;
*/
	// Bewegungsrichtungen
	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	
	// Schliessen auf false (0)
	int running = 1;
	
	/*  // Controller 
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
	printf("Controller Name: %s\n", SDL_JoystickName(joystick));
	printf("test");
	printf("Num Axes: %d\n", SDL_JoystickNumAxes(joystick));
	printf("Num Buttons: %d\n", SDL_JoystickNumButtons(joystick));
	*/
	
	/* Animation */
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
				if (event.type == SDL_QUIT)
				{
					running = 0;
				}
				
				else if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_ESCAPE:
							running = 0;
							break;
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							up = 1;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							left = 1;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							down = 1;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							right = 1;
							break;
					}
				}
				
				else if (event.type == SDL_KEYUP)
				{
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							up = 0;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							left = 0;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							down = 0;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							right = 0;
							break;
					}
				}
		}
		
		// Geschwindigkeit
		x_vel = y_vel = 0;
		if (up && !down) y_vel = -SPEED;
		if (down && !up) y_vel = SPEED;
		if (left && !right) x_vel = -SPEED;
		if (right && !left) x_vel = SPEED;
		
		// Positions Update
		x_pos += x_vel / FPS;
		y_pos += y_vel / FPS;
		
		// Kollision mit den Raendern
		if (x_pos <= 0) x_pos = 0;
		if (y_pos <= 0) y_pos = 0;
		if (x_pos >= RESOLUTION_WIDTH - dest.w) x_pos = RESOLUTION_WIDTH - dest.w;
		if (y_pos >= RESOLUTION_HEIGHT - dest.h) y_pos = RESOLUTION_HEIGHT - dest.h;
		
		// Positionen der Struct
		dest.y = (int) y_pos;
		dest.x = (int) x_pos;
		
		// Leere das Fenster
		SDL_RenderClear(rend);
		
		// Zeichne das Bild ins Fenster
		SDL_RenderCopy(rend, tex, NULL, &dest);
		SDL_RenderPresent(rend);
				
		// Fps
		SDL_Delay(1000/FPS);
	} /* Animation Ende */
	
	/* Resourcen schliessen */
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return 0;
}