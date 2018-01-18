#include "tetris.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

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
	{ // J
	{{0,2}, {1,0}, {1,1}, {1,2}},
	{{0,0}, {1,0}, {2,0}, {2,1}},
	{{0,0}, {0,1}, {0,2}, {1,0}},
	{{0,0}, {0,1}, {1,1}, {2,1}}},
	{ // O
	{{0,0}, {1,0}, {0,1}, {1,1}},
	{{0,0}, {1,0}, {0,1}, {1,1}},
	{{0,0}, {1,0}, {0,1}, {1,1}},
	{{0,0}, {1,0}, {0,1}, {1,1}}},
	{ // S
	{{1,0}, {0,1}, {1,1}, {0,2}},
	{{0,0}, {1,0}, {1,1}, {2,1}},
	{{1,0}, {0,1}, {1,1}, {0,2}},
	{{0,0}, {1,0}, {1,1}, {2,1}}},
	{ // T
	{{1,0}, {0,1}, {1,1}, {1,2}},
	{{0,0}, {1,0}, {2,0}, {1,1}},
	{{0,0}, {0,1}, {0,2}, {1,1}},
	{{0,1}, {1,1}, {2,1}, {1,0}}},
	{ // Z
	{{0,0}, {0,1}, {1,1}, {1,2}},
	{{0,1}, {1,1}, {1,0}, {2,0}},
	{{0,0}, {0,1}, {1,1}, {1,2}},
	{{0,1}, {1,1}, {1,0}, {2,0}}}
};
	
//Puts the next Block as the falling block and generates a new next Block.
void tetrisGetNextBlock (tetrisGame *game){
	block nextBlock;
	nextBlock.type = rand() % 7;
	nextBlock.orientation = 0;
	position posi;
	posi.x = (game->columns)/2;
	posi.y = 0;
	nextBlock.pos = posi;
	
	game->falling = game->next;
	game->next = nextBlock;
}

//Turns a Block clockwise.
void tetrisTurnBlockRight (tetrisGame *game){
	game->falling.orientation = (game->falling.orientation + 1) % 4;
	bool viable = true;
	for (int x = 0; x < game->columns; x++){
		for (int y = 0; y < game->rows; y++){
			for (int i = 0; i < 4; i++){
				int checkX = blockTypes[game->falling.type][game->falling.orientation][i].x + game->falling.pos.x;
				int checkY = blockTypes[game->falling.type][game->falling.orientation][i].y + game->falling.pos.y;
				if(checkY == game->rows || checkY < 0 || checkX < 0 || checkX == game->columns || game->map[checkY][checkX] != 0){
					viable = false;
				}
			}
		}
	}
	if(!viable){
		game->falling.pos.x -= 1;
	}
}

//Turns a Block counterclockwise.
void tetrisTurnBlockLeft (tetrisGame *game){
	game->falling.orientation -= 1;
	if(game->falling.orientation < 0){
		game->falling.orientation = 3;
	}
	bool viable = true;
	for (int x = 0; x < game->columns; x++){
		for (int y = 0; y < game->rows; y++){
			for (int i = 0; i < 4; i++){
				int checkX = blockTypes[game->falling.type][game->falling.orientation][i].x + game->falling.pos.x;
				int checkY = blockTypes[game->falling.type][game->falling.orientation][i].y + game->falling.pos.y;
				if(checkY == game->rows || checkY < 0 || checkX < 0 || checkX == game->columns || game->map[checkY][checkX] != 0){
					viable = false;
				}
			}
		}
	}
	if(!viable){
		game->falling.pos.x -= 1;
	}
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
		game->falling.pos.y -= 1;
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

void tetrisCheckLines (tetrisGame *game){
	int viableLines = 0;
	for(int y = 0; y < game->rows; y++){
		bool viable = true;
		for(int x = 0; x < game->columns; x++){
			if(game->map[y][x] == 0){
				viable = false;
			}
		}
		if(viable){
			viableLines += 1;
			for (int x = 0; x < game->columns; x++){
				game->map[y][x] = 0;
			}	
			for (int y2 = y; y2 > 0; y2--){
				for (int x = 0; x < game->columns; x++){
					game->map[y2][x] = game->map[y2-1][x];
				}
			}
		}
	}
}

//Returns information from the blockTypes Array to be used in other files.
position tetrisGetArrayInfo(int x, int y, int z){
	return blockTypes[x][y][z];
}