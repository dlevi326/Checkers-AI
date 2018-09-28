

#include <iostream>
#include <vector>
#include "Gameboard.h"
#include "Game.h"

using namespace std;


vector<vector<pair<int,int> > > Game::getValidMoves(Gameboard g, Gameboard::Square s){


	vector<vector<pair<int,int> > > moves;
	vector<pair<int,int> > tempMoves;
	tempMoves.push_back(make_pair(s.coords.first,s.coords.second));

	int i = s.coords.first;
	int j = s.coords.second;
	string blank = g.blankGame;
	string opposingPlayerKing, opposingPlayerReg; 

	int ind = -100;
	if(s.isKing){

		if(s.type==g.player1GameKing){
			ind = -1;
			opposingPlayerKing = g.player2GameKing;
			opposingPlayerReg = g.player2GameReg;
		}
		else if(s.type==g.player2GameKing){
			ind = 1;
			opposingPlayerKing = g.player1GameKing;
			opposingPlayerReg = g.player2GameReg;
		}
		else{
			return moves;
		}

		if (i+ind<g.board.size() && i+ind>=0){
			if(j+ind<g.board.size() && j+ind>=0){
				if(g.board[i+ind][j+ind].type==g.blankGame){
					tempMoves.push_back(make_pair(i+ind,j+ind));
					moves.push_back(tempMoves);
					tempMoves.pop_back();
				}
				else if(i+2*ind<g.board.size() && i+2*ind>=0){
					if(j+2*ind<g.board.size() && j+2*ind>=0){
						if(g.board[i+2*ind][j+2*ind].type==g.blankGame && (g.board[i+ind][j+ind].type==opposingPlayerReg || g.board[i+ind][j+ind].type==opposingPlayerReg)){
							tempMoves.push_back(make_pair(-1,-1));
							moves.push_back(tempMoves);
							tempMoves.pop_back();
							//getValidMoves(g,g.board[i+2*ind][j+2*ind]);
						}
					}
				}
			}
			if(j-ind<g.board.size() && j-ind>=0){
				if(g.board[i+ind][j-ind].type==g.blankGame){
					tempMoves.push_back(make_pair(i+ind,j-ind));
					moves.push_back(tempMoves);
					tempMoves.pop_back();
				}
			}
		}
		if(i-ind<g.board.size() && i-ind>=0){
			if(j+ind<g.board.size() && j+ind>=0){
				if(g.board[i-ind][j+ind].type==g.blankGame){
					tempMoves.push_back(make_pair(i-ind,j+ind));
					moves.push_back(tempMoves);
					tempMoves.pop_back();
				}
			}
			if(j-ind<g.board.size() && j-ind>=0){
				if(g.board[i-ind][j-ind].type==g.blankGame){
					tempMoves.push_back(make_pair(i-ind,j-ind));
					moves.push_back(tempMoves);
					tempMoves.pop_back();
				}
			}
		}

	}
	else{
		if(s.type==g.player1GameReg){
			ind = -1;
		}
		else if(s.type==g.player2GameReg){
			ind = 1;
		}
		else{
			return moves;
		}

		if(i-ind<g.board.size() && i-ind>=0){
			if(j+ind<g.board.size() && j+ind>=0){
				if(g.board[i-ind][j+ind].type==g.blankGame){
					tempMoves.push_back(make_pair(i-ind,j+ind));
					moves.push_back(tempMoves);
					tempMoves.pop_back();
				}
			}
			if(j-ind<g.board.size() && j-ind>=0){
				if(g.board[i-ind][j-ind].type==g.blankGame){
					tempMoves.push_back(make_pair(i-ind,j-ind));
					moves.push_back(tempMoves);
					tempMoves.pop_back();
				}
			}
		}

	}


	if(moves.size()==0){
		moves.push_back(tempMoves);
	}


	/*if(s.isKing){
		if(i+1<g.board.size() && i-1>=0 && j+1<g.board[0].size() && j-1>=0){
			moves.push_back(getValidMoves(g, g.board[i+1][j-1]));
			moves.push_back(getValidMoves(g, g.board[i+1][j+1]));
			moves.push_back(getValidMoves(g, g.board[i-1][j-1]));
			moves.push_back(getValidMoves(g, g.board[i-1][j+1]));
		}
	}
	else{
		if(i+1<g.board.size() && i-1>=0 && j+1<g.board[0].size() && j-1>=0){
			moves.push_back(getValidMoves(g, g.board[i-1][j-1]));
			moves.push_back(getValidMoves(g, g.board[i-1][j+1]));
		}
	}*/

	/*pair<int,int> currSquare = s.coords;

	if(currSquare.first-1>=0){
		if(currSquare.second-1>=0){
			if(!g.boardTrue[currSquare.first-1][currSquare.second-1]){
				moves.push_back(make_pair(currSquare.first-1,currSquare.second-1));
			}
		}
	}*/



	return moves;
}



Game::Game(){
	endGame = false;
}

void Game::printBoard(){
	for(int i=0;i<32;i++){
		cout<<"-";
	}
	cout<<endl;
	for(int i=0;i<currBoard.board.size();i++){
		for(int j=0;j<currBoard.board.size();j++){
			cout<<currBoard.board[i][j].type<<" ";
		}
		cout<<endl;
	}
	for(int i=0;i<32;i++){
		cout<<"-";
	}
	cout<<endl;
}

void Game::humanTurn(int turn){
	// Turn 1: player1
	// Turn 2: player2

	string targets[2];

	if(turn==1){
		targets[0] = currBoard.player1GameReg;
		targets[1] = currBoard.player1GameKing;
	} 
	else{
		targets[0] = currBoard.player2GameReg;
		targets[1] = currBoard.player2GameKing;
	}

	vector<vector<vector<pair<int,int> > > > allMoves;
	vector<vector<pair<int,int> > > temp;

	for(int i=0;i<currBoard.board.size();i++){
		for(int j=0;j<currBoard.board.size();j++){
			
			if(currBoard.board[i][j].type==targets[0] || currBoard.board[i][j].type==targets[1]){
				//cout<<"Getting valid moves for spot: "<<currBoard.board[i][j].coords.first<<" "<<currBoard.board[i][j].coords.second<<endl;
				temp = (getValidMoves(currBoard,currBoard.board[i][j]));
				allMoves.push_back(temp);
				//cout<<"Received: "<<temp[0].first<<" "<<temp[0].second<<endl;
			}
			
			
			temp.clear();
		}
	}

	//temp = (getValidMoves(currBoard,currBoard.board[1][5]));
	//allMoves.push_back(temp);

	for(int i=0;i<allMoves.size();i++){
		for(int j=0;j<allMoves[i].size();j++){
			for(int k=0;k<allMoves[i][j].size();k++){
				cout<<"("<<allMoves[i][j][k].first<<","<<allMoves[i][j][k].second<<") --> ";
			}
			cout<<endl;
		}
	}

}

void Game::compTurn(){

}

void Game::executeGame(Gameboard g,int whoseTurn, int gameType){
// gameType = 0: normal (1 comp vs 1 human)
// gameType = 1: (1 comp vs 1 comp)
// gameType = 2: (1 human vs 1 human)

// whoseTurn = 1: Human
// whoseTurn = 0: Comp 
	int num=0;
	int turn;
	(whoseTurn==0) ? turn = 1 : turn = -1;


	while(num<1){
		printBoard();

		switch(gameType){
			case 0:
				if(turn>0){
					humanTurn(turn);
					printBoard();
				}
				else{
					compTurn();
					printBoard();
				}
				turn*=-1;
			case 1:
				if(turn>0){
					compTurn();
					printBoard();
				}
				else{
					compTurn();
					printBoard();
				}
				turn*=-1;
			case 2:
				if(turn>0){
					humanTurn(turn);
					printBoard();
				}
				else{
					humanTurn(turn);
					printBoard();
				}
				turn*=-1;
		}
		num++;


	}


}










