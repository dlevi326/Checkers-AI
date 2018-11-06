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
	double minimax(int,int,Gameboard,bool,int,int,int,bool,bool,double,double,vector<vector<pair<int,int> > >);
	double getHeuristic(Gameboard,int,int);
	double getHeuristic1(Gameboard,int,int);
	double getHeuristic2(Gameboard,int,int);


	void printBoard(Gameboard);

	void executeGame(Gameboard,int=0,int=1, double=1,int=1); // Starts the game

	vector<vector<Gameboard::Square> > makeMove(Gameboard, vector<pair<int,int> >);

};




#endif