//
//  Board.c
//  TTT
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#include "Board.h"

#define opposite(p) (p) == PlayerComputer ? PlayerHuman : PlayerComputer

#define ALPHA PlayerHuman
#define BETA PlayerComputer

Boolean _BoardHasStraightWin (BoardRef board);
Boolean _BoardHasDiagonalWin (BoardRef board);
Player _BoardMinimax (BoardRef board, Player player, int alpha, int beta);

struct _Board {
	Player _state[TTT_ROWS][TTT_COLS];
};

Boolean _BoardHasStraightWin (BoardRef board) {
	for (int n = 0; n < TTT_ROWS; n++) {
		Player midX = board->_state[1][n];
		Player midY = board->_state[n][1];
		
		if (midX != PlayerNone) {
			if (board->_state[0][n] == midX && midX == board->_state[2][n])
				return true;
		}
		
		if (midY != PlayerNone) {
			if (board->_state[n][0] == midY && midY == board->_state[n][2])
				return true;
		}
	}
	
	return false;
}

Boolean _BoardHasDiagonalWin (BoardRef board) {
	Player mid = board->_state[1][1];
	
	if (mid == PlayerNone)
		return false;
	
	if ((board->_state[0][0] == mid && mid == board->_state[2][2]) || 
		(board->_state[0][2] == mid && mid == board->_state[2][0])) {
		
		return true;
	}
	
	return false;
}

Player _BoardMinimax (BoardRef board, Player player, int alpha, int beta) {
	if (BoardHasWin(board))
		return opposite(player);
	
	else if (BoardIsFull(board))
		return PlayerNone;
	
	for (int x = 0; x < TTT_COLS; x++) {
		for (int y = 0; y < TTT_ROWS; y++) {
			if (board->_state[x][y] == PlayerNone) {
				board->_state[x][y] = player;
				
				Player v = _BoardMinimax (board, opposite(player), alpha, beta);
				board->_state[x][y] = PlayerNone;
				
				if (player == PlayerComputer && v > alpha) {
					alpha = v;
					
					if (alpha >= beta)
						return alpha;
				}
				else if (player == PlayerHuman && v < beta) {
					beta = v;
					
					if (alpha >= beta)
						return beta;
				}
			}
		}
	}
	
	return player == PlayerComputer ? alpha : beta;
}

BoardRef BoardCreate (void) {
	BoardRef b = (BoardRef) malloc(sizeof(struct _Board));
	bzero(b->_state, sizeof(b->_state));
	
	return b;
}

void BoardRelease (BoardRef board) {
	free(board);
}

Boolean BoardIsFull (BoardRef board) {
	for (int x = 0; x < TTT_COLS; x++) {
		for (int y = 0; y < TTT_ROWS; y++) {
			if (board->_state[x][y] == PlayerNone)
				return false;
		}
	}
	
	return true;
}

Boolean BoardHasWin (BoardRef board) {
	return _BoardHasStraightWin(board) || _BoardHasDiagonalWin(board);
}

Player BoardPlayerAtCoordinate (BoardRef board, int x, int y) {
	return board->_state[x][y];
}

void BoardSetPlayerAtCoordinate (BoardRef board, int x, int y, Player player) {
	board->_state[x][y] = player;
}

Coordinate BoardFindBestComputerMove (BoardRef board) {
	int score = ALPHA, bestX = 0, bestY = 0;
	
	for (int x = 0; x < TTT_COLS; x++) {
		for (int y = 0; y < TTT_ROWS; y++) {
			if (board->_state[x][y] == PlayerNone) {
				board->_state[x][y] = PlayerComputer;
				
				Player v = _BoardMinimax(board, PlayerHuman, ALPHA, BETA);
				board->_state[x][y] = PlayerNone;
				
				if (v > score) {
					score = v, bestX = x, bestY = y;
				}
			}
		}
	}
	
	return (Coordinate) { .x = bestX, .y = bestY };
}
