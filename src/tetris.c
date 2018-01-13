#include "tetris.h"
#include <stdbool.h>

position blockTypes[7][4][4] = {
	{ // I
	{{0,0}, {0,1}, {0,2}, {0,3}},
	{{0,0}, {1,0}, {2,0}, {3,0}},
	{{0,0}, {0,1}, {0,2}, {0,3}},
	{{0,0}, {1,0}, {2,0}, {3,0}}},
	{ // L
	{{0,0}, {1,0}, {1,1}, {1,2}},
	{{0,0}, {1,0}, {2,0}, {0,1}},
	{{0,0}, {0,1}, {0,2}, {1,2}},
	{{0,1}, {1,1}, {2,1}, {2,0}}},
	{ // L reverse
	{{0,2}, {1,0}, {1,1}, {1,2}},
	{{0,0}, {1,0}, {2,0}, {2,1}},
	{{0,0}, {0,1}, {0,2}, {1,0}},
	{{0,0}, {0,1}, {1,1}, {2,1}}},
	{ // 2x2
	{{0,0}, {1,0}, {0,1}, {1,1}},
	{{0,0}, {1,0}, {0,1}, {1,1}},
	{{0,0}, {1,0}, {0,1}, {1,1}},
	{{0,0}, {1,0}, {0,1}, {1,1}}},
	{ // S
	{{1,0}, {0,1}, {1,1}, {0,2}},
	{{0,0}, {1,0}, {1,1}, {2,1}},
	{{1,0}, {0,1}, {1,1}, {0,2}},
	{{0,0}, {1,0}, {1,1}, {2,1}}},
	{ // T umgedreht
	{{1,0}, {0,1}, {1,1}, {1,2}},
	{{0,0}, {1,0}, {2,0}, {1,1}},
	{{0,0}, {0,1}, {0,2}, {1,1}},
	{{0,1}, {1,1}, {2,1}, {1,0}}},
	{ // S reverse
	{{0,0}, {0,1}, {1,1}, {1,2}},
	{{0,1}, {1,1}, {1,0}, {2,0}},
	{{0,0}, {0,1}, {1,1}, {1,2}},
	{{0,1}, {1,1}, {1,0}, {2,0}}}
};
	
	

void tetrisGetNextBlock (tetrisGame *game){
	block nextBlock;
	nextBlock.type = rand() % 8;
	nextBlock.orientation = 0;
	position posi;
	posi.x = (game->rows)/2;
	posi.y = 0;
	nextBlock.pos = posi;
	game->falling = game->next;
	game->next = nextBlock;
}

void tetrisTurnBlock (tetrisGame *game){
	game->falling.orientation = (game->falling.orientation + 1) % 4;
}

void tetrisApplyGravity (tetrisGame *game){
	game->falling.pos.x -= 1;
	bool viable = true;
	for (int x = 0; x < game->columns; x++){
		for (int y = 0; y < game->rows; y++){
			for (int i = 0; i < 4; i++){
				int checkX = blockTypes[game->falling.type][game->falling.orientation][i].x + game->falling.pos.x;
				int checkY = blockTypes[game->falling.type][game->falling.orientation][i].y + game->falling.pos.y;
				if(game->map[checkY][checkX] != 0){
					viable = false;
				}
			}
		}
	}
	if(!viable){
		game->falling.pos.x += 1;
	}
}
