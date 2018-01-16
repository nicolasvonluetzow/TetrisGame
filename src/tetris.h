#include <stdlib.h>

//Position contains x and y coordinates
typedef struct {
	int x, y;	
} position;

//Block contains type (implies color), orientation and position
typedef struct {
	int type, orientation;
	position pos;
} block;

//TetrisGame contains all relevant information about the game.
typedef struct {
	int rows, columns, score, level;
	short map[20][10];
	block falling, next;
} tetrisGame;

//Function declarations (explained when used)
void tetrisGetNextBlock (tetrisGame *game);
void tetrisTurnBlockRight (tetrisGame *game);
void tetrisTurnBlockLeft (tetrisGame *game);
void tetrisApplyGravity (tetrisGame *game);
void tetrisMoveLeft (tetrisGame *game);
void tetrisMoveRight (tetrisGame *game);
void tetrisAddToMap (tetrisGame *game);
void tetrisCheckLines (tetrisGame *game);
position tetrisGetArrayInfo(int x, int y, int z);
