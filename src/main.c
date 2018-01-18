#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tetris.h"

#ifdef __MINGW32__
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2_mixer/SDL_mixer.h>
#endif


#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720
#define FPS 60
#define STARTLEVEL 0
#define MAXLEVEL 20

int main(int argc, char *argv[])
{
	// Pixels per Block
	int PpB = RESOLUTION_HEIGHT / 25;
	srand(time(NULL));

	tetrisGame game;
	tetrisGame* pointGame;
	pointGame = &game;
	game.rows = 20;
	game.columns = 10;
	game.score = 0;
	game.level = 0;
	game.lines = 0;
	block fall;
	fall.type = 0;
	game.falling = fall;
	block nex;
	nex.type = 0;
	game.next = nex;
	
	FILE *print;
	print = fopen("output.txt", "w");
	
	int *LinesNeeded = (int*) malloc(MAXLEVEL*sizeof(int));
	for (int i = 0, k = 10; i < MAXLEVEL; i++, k+=10)
	{
		LinesNeeded[i] = k;
	}
	
	int* pLinesNeeded = LinesNeeded;
	for (int i = 0; i < STARTLEVEL; i++, pLinesNeeded++);
	
	int renderMap[game.rows][game.columns];

	tetrisGetNextBlock (pointGame);
	tetrisGetNextBlock (pointGame);

	/* Init map */
	for (int x = 0; x < game.columns; x++)
	{
		for (int y = 0; y < game.rows; y++)
		{
			game.map[y][x] = 0;
		}
	}

	for (int x = 0; x < game.columns; x++)
	{
		for (int y = 0; y < game.rows; y++)
		{
			renderMap[y][x] = 0;
		}
	}


	/* Anfang Basic Framework */
	if (SDL_Init( SDL_INIT_VIDEO| SDL_INIT_AUDIO | SDL_INIT_TIMER ) < 0)
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


	SDL_Surface* BlockI = IMG_Load("textures/TexBlockI.png");
	SDL_Surface* BlockL = IMG_Load("textures/TexBlockL.png");
	SDL_Surface* BlockJ = IMG_Load("textures/TexBlockJ.png");
	SDL_Surface* BlockO = IMG_Load("textures/TexBlockO.png");
	SDL_Surface* BlockS = IMG_Load("textures/TexBlockS.png");
	SDL_Surface* BlockT = IMG_Load("textures/TexBlockT.png");
	SDL_Surface* BlockZ = IMG_Load("textures/TexBlockZ.png");
	SDL_Surface* Edges = IMG_Load("textures/Edges.png");
	SDL_Surface* BackgroundImage = IMG_Load("textures/Background.jpg");



	if (!(BlockI || BlockL || BlockJ || BlockO || BlockS || BlockT || BlockZ || Edges || BackgroundImage))
	{
		printf("Fehler beim Initialisieren von mindestens einer der Oberflaechen: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	SDL_Texture* texBlockI = SDL_CreateTextureFromSurface(rend, BlockI);
	SDL_Texture* texBlockL = SDL_CreateTextureFromSurface(rend, BlockL);
	SDL_Texture* texBlockJ = SDL_CreateTextureFromSurface(rend, BlockJ);
	SDL_Texture* texBlockO = SDL_CreateTextureFromSurface(rend, BlockO);
	SDL_Texture* texBlockS = SDL_CreateTextureFromSurface(rend, BlockS);
	SDL_Texture* texBlockT = SDL_CreateTextureFromSurface(rend, BlockT);
	SDL_Texture* texBlockZ = SDL_CreateTextureFromSurface(rend, BlockZ);
	SDL_Texture* texEdges = SDL_CreateTextureFromSurface(rend, Edges);
	SDL_Texture* texBackgroundImage = SDL_CreateTextureFromSurface(rend, BackgroundImage);
	SDL_FreeSurface(BlockI);
	SDL_FreeSurface(BlockL);
	SDL_FreeSurface(BlockJ);
	SDL_FreeSurface(BlockO);
	SDL_FreeSurface(BlockS);
	SDL_FreeSurface(BlockT);
	SDL_FreeSurface(BlockZ);
	SDL_FreeSurface(Edges);
	SDL_FreeSurface(BackgroundImage);

	/* Fehlercode an die neuen Texturen anpassen */
	if (!(texBlockI || texBlockL || texBlockJ || texBlockS || texBlockT || texBlockO || texBlockZ || texEdges || texBackgroundImage))
	{
		printf("Fehler beim Erstellen der Textur: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	/* Ende Basic Framework */

	/* Music */
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* BackgroundMusic = Mix_LoadMUS("music/BackgroundMusic.mp3");
	Mix_PlayMusic(BackgroundMusic, -1);


	//Struct der Position und Groesse des Sprites
	SDL_Rect RBlockI;
	SDL_Rect RBlockL;
	SDL_Rect RBlockJ;
	SDL_Rect RBlockO;
	SDL_Rect RBlockS;
	SDL_Rect RBlockT;
	SDL_Rect RBlockZ;
	SDL_Rect REdges;


	//Dimension der Textur
	SDL_QueryTexture(texBlockI, NULL, NULL, &RBlockI.w, &RBlockI.h);
	SDL_QueryTexture(texBlockL, NULL, NULL, &RBlockL.w, &RBlockL.h);
	SDL_QueryTexture(texBlockJ, NULL, NULL, &RBlockJ.w, &RBlockJ.h);
	SDL_QueryTexture(texBlockO, NULL, NULL, &RBlockO.w, &RBlockO.h);
	SDL_QueryTexture(texBlockS, NULL, NULL, &RBlockS.w, &RBlockS.h);
	SDL_QueryTexture(texBlockT, NULL, NULL, &RBlockT.w, &RBlockT.h);
	SDL_QueryTexture(texBlockZ, NULL, NULL, &RBlockZ.w, &RBlockZ.h);
	SDL_QueryTexture(texEdges, NULL, NULL, &REdges.w, &REdges.h);

	// Bewegungsrichtungen
	int down = 0;
	int Gravity = 0;
	int oldlines = 0;

	/*  // Controller
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
	printf("Controller Name: %s\n", SDL_JoystickName(joystick));
	printf("test");
	printf("Num Axes: %d\n", SDL_JoystickNumAxes(joystick));
	printf("Num Buttons: %d\n", SDL_JoystickNumButtons(joystick));
	*/
	
	game.running = true;

	/* Animation */
	while (game.running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
				if (event.type == SDL_QUIT)
				{
					game.running = false;
				}

				else if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_ESCAPE:
							game.running = false;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							tetrisMoveLeft(pointGame);
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							down = 1;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							tetrisMoveRight(pointGame);
							break;
						case SDL_SCANCODE_Q:
							tetrisTurnBlockLeft(pointGame);
							break;
						case SDL_SCANCODE_E:
							tetrisTurnBlockRight(pointGame);
							break;
						default:
							break;
					}
				}

				else if (event.type == SDL_KEYUP)
				{
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							down = 0;
							break;
						default:
							break;
					}
				}

		}


		if (down)
		{
			tetrisApplyGravity(pointGame);
		}


		/* Gravity */
		if (Gravity >= FPS)
		{
			tetrisApplyGravity(pointGame);
			Gravity -= FPS;
		}


		// Leere das Fenster
		SDL_RenderClear(rend);

		/* Neue Texturen auf die Map */
		for (int x = 0; x < game.columns; x++){
			for (int y = 0; y < game.rows; y++){
				renderMap[y][x] = game.map[y][x];
			}
		}

		for (int i = 0; i < 4; i++){
			int checkX = tetrisGetArrayInfo(game.falling.type, game.falling.orientation, i).x + game.falling.pos.x;
			int checkY = tetrisGetArrayInfo(game.falling.type, game.falling.orientation, i).y + game.falling.pos.y;
			renderMap[checkY][checkX] = game.falling.type + 1;
		}

		/* Background */
		SDL_RenderCopy(rend, texBackgroundImage, NULL, NULL);


		/* Edges Start */
		for (int y = 0; y < game.rows; y++)
		{
			REdges.x = -1 * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
			REdges.y = y * PpB + 3*PpB;
				SDL_RenderCopy(rend, texEdges, NULL, &REdges);
		}
		for (int y = 0; y < game.rows; y++)
		{
			REdges.x = game.columns * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
			REdges.y = y * PpB + 3*PpB;
				SDL_RenderCopy(rend, texEdges, NULL, &REdges);
		}
		for (int x = -1; x < (game.columns + 1); x++)
		{
			REdges.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
			REdges.y = -1 * PpB + 3*PpB;
				SDL_RenderCopy(rend, texEdges, NULL, &REdges);
		}
		for (int x = -1; x < (game.columns + 1); x++)
		{
			REdges.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
			REdges.y = game.rows * PpB + 3*PpB;
				SDL_RenderCopy(rend, texEdges, NULL, &REdges);
		}
		/* Edges Ende */


		for (int x = 0; x < game.columns; x++)
		{
			for (int y = 0; y < game.rows; y++)
			{
				switch (renderMap[y][x])
				{
					case 0: break;
					case 1: RBlockI.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
							RBlockI.y = y * PpB + 3*PpB;
								SDL_RenderCopy(rend, texBlockI, NULL, &RBlockI);
							break;
					case 2: RBlockL.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
							RBlockL.y = y * PpB + 3*PpB;
								SDL_RenderCopy(rend, texBlockL, NULL, &RBlockL);
							break;
					case 3: RBlockJ.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
							RBlockJ.y = y * PpB + 3*PpB;
								SDL_RenderCopy(rend, texBlockJ, NULL, &RBlockJ);
							break;
					case 4: RBlockS.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
							RBlockS.y = y * PpB + 3*PpB;
								SDL_RenderCopy(rend, texBlockS, NULL, &RBlockS);
							break;
					case 5: RBlockT.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
							RBlockT.y = y * PpB + 3*PpB;
								SDL_RenderCopy(rend, texBlockT, NULL, &RBlockT);
							break;
					case 6: RBlockO.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
							RBlockO.y = y * PpB + 3*PpB;
								SDL_RenderCopy(rend, texBlockO, NULL, &RBlockO);
							break;
					case 7: RBlockZ.x = x * PpB + (RESOLUTION_WIDTH/2) - 5*PpB;
							RBlockZ.y = y * PpB + 3*PpB;
								SDL_RenderCopy(rend, texBlockZ, NULL, &RBlockZ);
							break;
					default: break;
				}
			}
		}
		
		tetrisCheckLines(pointGame);
		// pointer an tetrisCheckLines() übergeben, hier weiterarbeiten
		if (game.lines >= (*pLinesNeeded) && ((*pLinesNeeded) < 10*MAXLEVEL))
		{
			pLinesNeeded++;
			int shouldBeLevel = ((*pLinesNeeded - 10) /10);
			for (; game.level < shouldBeLevel; game.level++);
		}
			
		if (oldlines != game.lines)
		{
			fprintf(print, "Lines: %d\n", game.lines);
			fprintf(print, "Score: %d\n", game.score);
			fprintf(print, "Level: %d\n\n", game.level);
		}
		
		oldlines = game.lines;
		SDL_RenderPresent(rend);


		/* On every Frame */
		SDL_Delay(1000/FPS);
		Gravity+= 2*(game.level + 1);




	} /* Animation Ende */

	/* Resourcen schliessen */
	SDL_DestroyTexture(texBlockI);
	SDL_DestroyTexture(texBlockL);
	SDL_DestroyTexture(texBlockJ);
	SDL_DestroyTexture(texBlockS);
	SDL_DestroyTexture(texBlockT);
	SDL_DestroyTexture(texBlockO);
	SDL_DestroyTexture(texBlockZ);
	SDL_DestroyTexture(texEdges);
	SDL_DestroyTexture(texBackgroundImage);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	free(LinesNeeded);
	fclose(print);
	
	return 0;
}
