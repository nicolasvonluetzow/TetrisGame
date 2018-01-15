#include "tetris.h"
#include <stdbool.h>
#include <stdio.h>

//Array contains all BlockTypes and all possible orientation
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
	
//Puts the next Block as the falling block and generates a new next Block.
void tetrisGetNextBlock (tetrisGame *game){
	block nextBlock;
	nextBlock.type = rand() % 8;
	nextBlock.orientation = 0;
	position posi;
	posi.x = (game->columns)/2;
	posi.y = 0;
	nextBlock.pos = posi;
	
	game->falling = game->next;
	game->next = nextBlock;
}

//Turns a Block clockwise.
void tetrisTurnBlock (tetrisGame *game){
	game->falling.orientation = (game->falling.orientation + 1) % 4;
}

//Applies gravity once. Not to be called every tick.
void tetrisApplyGravity (tetrisGame *game){
	game->falling.pos.y += 1; //wo "+" war vorher "-"
	bool viable = true;
	for (int x = 0; x < game->columns; x++){
		for (int y = 0; y < game->rows; y++){
			for (int i = 0; i < 4; i++){
				int checkX = blockTypes[game->falling.type][game->falling.orientation][i].x + game->falling.pos.x;
				int checkY = blockTypes[game->falling.type][game->falling.orientation][i].y + game->falling.pos.y;
				if(checkY == game->rows || game->map[checkY][checkX] != 0){
					viable = false;
				}
			}
		}
	}
	if(!viable){
		game->falling.pos.y += 1;
		tetrisAddToMap(game);
	}
}

//Moves the falling block to the left.
void tetrisMoveLeft (tetrisGame *game){
	game->falling.pos.x -= 1;
	bool viable = true;
	for (int x = 0; x < game->columns; x++){
		for (int y = 0; y < game->rows; y++){
			for (int i = 0; i < 4; i++){
				int checkX = blockTypes[game->falling.type][game->falling.orientation][i].x + game->falling.pos.x;
				int checkY = blockTypes[game->falling.type][game->falling.orientation][i].y + game->falling.pos.y;
				if(game->map[checkY][checkX] != 0 || checkX < 0){
					viable = false;
				}
			}
		}
	}
	if(!viable){
		game->falling.pos.x += 1;
	}
}

//Moves the falling block to the right.
void tetrisMoveRight (tetrisGame *game){
	game->falling.pos.x += 1;
	bool viable = true;
	for (int x = 0; x < game->columns; x++){
		for (int y = 0; y < game->rows; y++){
			for (int i = 0; i < 4; i++){
				int checkX = blockTypes[game->falling.type][game->falling.orientation][i].x + game->falling.pos.x;
				int checkY = blockTypes[game->falling.type][game->falling.orientation][i].y + game->falling.pos.y;
				if(game->map[checkY][checkX] != 0 || checkX >= game->columns){
					viable = false;
				}
			}
		}
	}
	if(!viable){
		game->falling.pos.x -= 1;
	}
}

//Adds the falling Block to the map and generates a new Block.
void tetrisAddToMap (tetrisGame *game){
	for (int i = 0; i < 4; i++){
		int checkX = blockTypes[game->falling.type][game->falling.orientation][i].x + game->falling.pos.x;
		int checkY = blockTypes[game->falling.type][game->falling.orientation][i].y + game->falling.pos.y;
		game->map[checkY][checkX] = game->falling.type + 1;
	}
	tetrisGetNextBlock(game);
}

position tetrisGetArrayInfo(int x, int y, int z){
	return blockTypes[x][y][z];
}