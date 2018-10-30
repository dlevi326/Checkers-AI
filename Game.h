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
	void compTurn(int,double);

	vector<vector<pair<int,int> > > getValidMoves(Gameboard, Gameboard::Square); // Gets all valid moves of a piece

	vector<vector<pair<int,int> > > getValidMovesJump(Gameboard, Gameboard::Square, vector<pair<int,int> >);

	vector<vector<pair<int,int> > > getMoves(int,Gameboard);

	Game(); // Init

	int makeMove1(vector<vector<pair<int,int> > >, Gameboard,double);
	int makeMove2(vector<vector<pair<int,int> > >, Gameboard,double);
	int minimax(int,Gameboard,bool,int,int,int,bool);
	int getHeuristic(Gameboard,int);
	int getHeuristic2(Gameboard,int);


	void printBoard(Gameboard);

	void executeGame(Gameboard,int=0,int=1, double=1); // Starts the game

	vector<vector<Gameboard::Square> > makeMove(Gameboard, vector<pair<int,int> >);

};




#endif