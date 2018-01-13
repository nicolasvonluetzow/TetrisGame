#include <stdlib.h>

typedef struct {
	int x, y;	
} position;

typedef struct {
	int type, orientation;
	position pos;
} block;

typedef struct {
	int rows, columns, score, level;
	int map[10][10];
	block falling, next;
} tetrisGame;

void tetrisGetNextBlock (tetrisGame *game);
void tetrisTurnBlock (tetrisGame *game);
void tetrisApplyGravity (tetrisGame *game);
void tetrisMoveLeft (tetrisGame *game);
void tetrisMoveRight (tetrisGame *game);
void tetrisAddToMap (tetrisGame *game);