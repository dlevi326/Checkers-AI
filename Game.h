#ifndef __GAME_h__
#define __GAME_h__

#include <iostream>
#include <vector>
#include "Gameboard.h"
#include "Square.h"

using namespace std;

class Game{
public:

	vector<Gameboard> oldBoards;
	Gameboard currBoard;

	//vector<pair<int,int> > getValidMoves(Gameboard g, Square s); // Gets all valid moves of a piece

	Game();

	void printBoard();

};

/*vector<pair<int,int> > Game::getValidMoves(Gameboard g, Square s){
	vector<pair<int,int> > moves;
	pair<int,int> currSquare = s.coords;

	if(currSquare.first-1>=0){
		if(currSquare.second-1>=0){
			if(!g.boardTrue[currSquare.first-1][currSquare.second-1]){
				moves.push_back(make_pair(currSquare.first-1,currSquare.second-1));
			}
		}
	}



	return moves;
}*/

/*Game::Game(){

}

void Game::printBoard(){
	for(int i=0;i<currBoard.board.size();i++){
		for(int j=0;j<currBoard.board.size();j++){
			cout<<currBoard.board[i][j].type<<" ";
		}
		cout<<endl;
	}
}*/










#endif