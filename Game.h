#ifndef __GAME_h__
#define __GAME_h__

#include <iostream>
#include <vector>
#include "Gameboard.h"

using namespace std;

class Game{
public:


	vector<Gameboard> oldBoards; // Vector of all old boards
	Gameboard currBoard; // Current gameboard
	bool endGame; // Did game end

	void humanTurn(int);
	void compTurn();

	vector<vector<pair<int,int> > > getValidMoves(Gameboard, Gameboard::Square); // Gets all valid moves of a piece

	Game(); // Init

	void printBoard();

	void executeGame(Gameboard,int=0,int=0); // Starts the game

};




#endif