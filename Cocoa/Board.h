//
//  Board.h
//  TTT
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#include <CoreFoundation/CoreFoundation.h>

#define TTT_ROWS 3
#define TTT_COLS 3

typedef struct _Board *BoardRef;

enum _Player {
	PlayerHuman = -1,
	PlayerNone,
	PlayerComputer
};
typedef enum _Player Player;

struct _Coordinate {
	int x;
	int y;
};
typedef struct _Coordinate Coordinate;


BoardRef BoardCreate (void);
void BoardRelease (BoardRef board);

Boolean BoardIsFull (BoardRef board);
Boolean BoardHasWin (BoardRef board);

Player BoardPlayerAtCoordinate (BoardRef board, int x, int y);
void BoardSetPlayerAtCoordinate (BoardRef board, int x, int y, Player player);

Coordinate BoardFindBestComputerMove (BoardRef board);
