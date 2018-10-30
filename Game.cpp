

#include <iostream>
#include <vector>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <time.h> 
#include <ctime>
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
			opposingPlayerReg = g.player1GameReg;
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
							tempMoves.push_back(make_pair(i+(2*ind),j+(2*ind)));
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


	return moves;
}

bool inBoundsNK(Gameboard::Square s,int first, int second){
	// In bounds no king

	if(first>7 || first<0 || second>7 || second<0){
		return false;
	}
	return true;

}

vector<vector<pair<int,int> > > Game::getValidMovesJump(Gameboard g, Gameboard::Square s, vector<pair<int,int> > currPath){
	//cout<<"GETTING MOVES JUMPS "<<s.coords.first<<" "<<s.coords.second<<endl;

	int ind;
	string oppPlayer[2];
	if(s.type==g.player1GameReg || s.type==g.player1GameKing){
		ind = -1;
		oppPlayer[0] = g.player2GameReg;
		oppPlayer[1] = g.player2GameKing;
	}
	else{
		ind = 1;
		oppPlayer[0] = g.player1GameReg;
		oppPlayer[1] = g.player1GameKing;
	}

	vector<vector<pair<int,int> > > moves;

	currPath.push_back(make_pair(s.coords.first,s.coords.second));
	//moves.push_back(currPath);

	vector<vector<Gameboard::Square> > newBoard;
	Gameboard newGameboard;


	if(!s.isKing || s.isKing){
		if(inBoundsNK(s,s.coords.first-(2*ind),s.coords.second-(2*ind))){
			if((g.board[s.coords.first-(ind)][s.coords.second-(ind)].type==oppPlayer[0] || g.board[s.coords.first-(ind)][s.coords.second-(ind)].type==oppPlayer[1])
				&& g.board[s.coords.first-(2*ind)][s.coords.second-(2*ind)].type==g.blankGame){

				vector<pair<int,int> > makeMoveVect;
				makeMoveVect.push_back(make_pair(s.coords.first,s.coords.second));
				makeMoveVect.push_back(make_pair(s.coords.first-(2*ind),s.coords.second-(2*ind)));

				newBoard = makeMove(g,makeMoveVect);
				newGameboard.board = newBoard;
				//cout<<"Printing modified board.."<<endl;
				//printBoard(newGameboard);

				vector<vector<pair<int,int> > > temp = getValidMovesJump(newGameboard,newGameboard.board[s.coords.first-(2*ind)][s.coords.second-(2*ind)],currPath);
				if(temp.size()==0){
					// Dont think this ever executes
					currPath.push_back(make_pair(s.coords.first-(2*ind),s.coords.second-(2*ind)));
					moves.push_back(currPath);
					currPath.pop_back();
				}
				//moves.insert(moves.begin(),temp.begin(),temp.end());
				// Should I add this ^^^^^ ???? check


				for(int i=0;i<temp.size();i++){
					moves.push_back(temp[i]);
				}

			}
		}
		if(inBoundsNK(s,s.coords.first-(2*ind),s.coords.second+(2*ind))){
			if((g.board[s.coords.first-(ind)][s.coords.second+(ind)].type==oppPlayer[0] || g.board[s.coords.first-(ind)][s.coords.second+(ind)].type==oppPlayer[1])
				&& g.board[s.coords.first-(2*ind)][s.coords.second+(2*ind)].type==g.blankGame){

				vector<pair<int,int> > makeMoveVect;
				makeMoveVect.push_back(make_pair(s.coords.first,s.coords.second));
				makeMoveVect.push_back(make_pair(s.coords.first-(2*ind),s.coords.second+(2*ind)));

				newBoard = makeMove(g,makeMoveVect);
				newGameboard.board = newBoard;
				//cout<<"Printing modified board.."<<endl;
				//printBoard(newGameboard);


				if(moves.size()==1){
					//currPath.pop_back();
				}
				

				vector<vector<pair<int,int> > > temp = getValidMovesJump(newGameboard,newGameboard.board[s.coords.first-(2*ind)][s.coords.second+(2*ind)],currPath);
				//moves.insert(moves.begin(),temp.begin(),temp.end());
				// Should I add this ^^^^^ ???? check

				if(temp.size()==0){
					currPath.push_back(make_pair(s.coords.first-(2*ind),s.coords.second+(2*ind)));
					moves.push_back(currPath);
					currPath.pop_back();
				}

				for(int i=0;i<temp.size();i++){
					moves.push_back(temp[i]);
				}

			}
		}
	}
	if(s.isKing){
		if(inBoundsNK(s,s.coords.first+(2*ind),s.coords.second-(2*ind))){
			if((g.board[s.coords.first+(ind)][s.coords.second-(ind)].type==oppPlayer[0] || g.board[s.coords.first+(ind)][s.coords.second-(ind)].type==oppPlayer[1])
				&& g.board[s.coords.first+(2*ind)][s.coords.second-(2*ind)].type==g.blankGame){

				vector<pair<int,int> > makeMoveVect;
				makeMoveVect.push_back(make_pair(s.coords.first,s.coords.second));
				makeMoveVect.push_back(make_pair(s.coords.first+(2*ind),s.coords.second-(2*ind)));

				newBoard = makeMove(g,makeMoveVect);
				newGameboard.board = newBoard;
				//cout<<"Printing modified board.."<<endl;
				//printBoard(newGameboard);


				if(moves.size()==1){
					//currPath.pop_back();
				}
				

				vector<vector<pair<int,int> > > temp = getValidMovesJump(newGameboard,newGameboard.board[s.coords.first+(2*ind)][s.coords.second-(2*ind)],currPath);
				//moves.insert(moves.begin(),temp.begin(),temp.end());
				// Should I add this ^^^^^ ???? check

				if(temp.size()==0){
					currPath.push_back(make_pair(s.coords.first+(2*ind),s.coords.second-(2*ind)));
					moves.push_back(currPath);
					currPath.pop_back();
				}

				for(int i=0;i<temp.size();i++){
					moves.push_back(temp[i]);
				}

			}
		}
		if(inBoundsNK(s,s.coords.first+(2*ind),s.coords.second+(2*ind))){
			if((g.board[s.coords.first+(ind)][s.coords.second+(ind)].type==oppPlayer[0] || g.board[s.coords.first+(ind)][s.coords.second+(ind)].type==oppPlayer[1])
				&& g.board[s.coords.first+(2*ind)][s.coords.second+(2*ind)].type==g.blankGame){

				vector<pair<int,int> > makeMoveVect;
				makeMoveVect.push_back(make_pair(s.coords.first,s.coords.second));
				makeMoveVect.push_back(make_pair(s.coords.first+(2*ind),s.coords.second+(2*ind)));

				newBoard = makeMove(g,makeMoveVect);
				newGameboard.board = newBoard;
				//cout<<"Printing modified board.."<<endl;
				//printBoard(newGameboard);

				if(moves.size()==1){
					//currPath.pop_back();
				}
				

				vector<vector<pair<int,int> > > temp = getValidMovesJump(newGameboard,newGameboard.board[s.coords.first+(2*ind)][s.coords.second+(2*ind)],currPath);
				//moves.insert(moves.begin(),temp.begin(),temp.end());
				// Should I add this ^^^^^ ???? check

				if(temp.size()==0){
					currPath.push_back(make_pair(s.coords.first+(2*ind),s.coords.second+(2*ind)));
					moves.push_back(currPath);
					currPath.pop_back();
				}

				for(int i=0;i<temp.size();i++){
					moves.push_back(temp[i]);
				}

			}
		}
	}


	//moves.push_back(currPath);

	return moves;

}

int inputMove(vector<vector<pair<int,int> > > allMoves){
	int moveNum = -1;
	cin>>moveNum;
	
	if(!cin){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Invalid move number, please choose again: ";
		//cin>>moveNum;
		return -1;
	}
	if(moveNum>=allMoves.size() || moveNum<0){
		cout<<"Invalid number, please choose again: ";
		return -1;
	}
	else{
		return moveNum;
	}
	

}


Game::Game(){
	endGame = false;
}

void Game::printBoard(Gameboard g){
	for(int i=0;i<35;i++){
		cout<<"-";
	}
	cout<<endl;
	cout<<"     ";
	for(int i=0;i<8;i++){
		cout<<"\033[1;30m"<<"("<<i<<")"<<"\033[0m";
	}
	cout<<endl;
	for(int i=0;i<g.board.size();i++){
		cout<<"\033[1;30m("<<i<<")\033[0m  ";
		for(int j=0;j<g.board.size();j++){
			if(g.board[i][j].type==g.player1GameReg||g.board[i][j].type==g.player1GameKing){
				cout<<"\033[7;31m";
			}
			else if(g.board[i][j].type==g.player2GameReg||g.board[i][j].type==g.player2GameKing){
				cout<<"\033[7;30m";
			}
			else if(g.board[i][j].type==g.blankGame){
				cout<<"\033[7;36m";
			}
			cout<<g.board[i][j].type;
			cout<<"\033[0m";
		}
		cout<<endl;
	}
	for(int i=0;i<35;i++){
		cout<<"-";
	}
	cout<<endl;
}

bool isJump(pair<int,int> m1, pair<int,int> m2){
	if(abs(m1.first-m2.first)==2){
		return true;
	}
	return false;
}

vector<vector<Gameboard::Square> > Game::makeMove(Gameboard g, vector<pair<int,int> > move){

	string currPiece;
	bool isKing;

	string currType = g.board[move[0].first][move[0].second].type;
	int kingYcoord;
	if(currType==g.player1GameReg || currType==g.player1GameKing){
		kingYcoord = 7;
	}
	else{
		kingYcoord = 0;
	}


	for(int i=0;i<move.size()-1;i++){
		if(!isJump(move[i],move[i+1])){

			currPiece = g.board[move[i].first][move[i].second].type;
			isKing = g.board[move[i].first][move[i].second].isKing;

			g.board[move[i].first][move[i].second].type = g.blankGame;
			g.board[move[i].first][move[i].second].isKing = false;

			g.board[move[i+1].first][move[i+1].second].type = currPiece;
			g.board[move[i+1].first][move[i+1].second].isKing = isKing;

			if(move[i+1].first==kingYcoord && kingYcoord==7){
				g.board[move[i+1].first][move[i+1].second].isKing = true;
				g.board[move[i+1].first][move[i+1].second].type = g.player1GameKing;
			}
			else if(move[i+1].first==kingYcoord && kingYcoord==0){
				g.board[move[i+1].first][move[i+1].second].isKing = true;
				g.board[move[i+1].first][move[i+1].second].type = g.player2GameKing;
			}
			else{
				g.board[move[i+1].first][move[i+1].second].type = currPiece;
				g.board[move[i+1].first][move[i+1].second].isKing = isKing;
			}
		}
		else{
			int xJump = (move[i].first+move[i+1].first)/2;
			int yJump = (move[i].second+move[i+1].second)/2;

			currPiece = g.board[move[i].first][move[i].second].type;
			isKing = g.board[move[i].first][move[i].second].isKing;

			g.board[move[i].first][move[i].second].type = g.blankGame;
			g.board[move[i].first][move[i].second].isKing = false;

			g.board[xJump][yJump].type = g.blankGame;
			g.board[xJump][yJump].isKing = false;

			if(move[i+1].first==kingYcoord && kingYcoord==7){
				g.board[move[i+1].first][move[i+1].second].isKing = true;
				g.board[move[i+1].first][move[i+1].second].type = g.player1GameKing;
			}
			else if(move[i+1].first==kingYcoord && kingYcoord==0){
				g.board[move[i+1].first][move[i+1].second].isKing = true;
				g.board[move[i+1].first][move[i+1].second].type = g.player2GameKing;
			}
			else{
				g.board[move[i+1].first][move[i+1].second].type = currPiece;
				g.board[move[i+1].first][move[i+1].second].isKing = isKing;
			}
			
		}

	}

	return g.board;
}

vector<vector<pair<int,int> > > Game::getMoves(int turn,Gameboard g){
	string targets[2];

	if(turn==1){
		targets[0] = g.player1GameReg;
		targets[1] = g.player1GameKing;
	} 
	else{
		targets[0] = g.player2GameReg;
		targets[1] = g.player2GameKing;
	}

	vector<vector<pair<int,int> > > allMoves;
	vector<vector<pair<int,int> > > temp;

	bool isJumpPossible = false;

	for(int i=0;i<g.board.size();i++){
		for(int j=0;j<g.board.size();j++){
			
			if(g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]){
				vector<pair<int,int> > path;
				
				temp = (getValidMovesJump(g,g.board[i][j],path));
				

				if(temp.size()>0){
					isJumpPossible = true;
					for(int k=0;k<temp.size();k++){
						if(temp[k].size()>0){
							allMoves.push_back(temp[k]);
						}
					}	
				}
				
			}
			temp.clear();
		}
	}


	if(!isJumpPossible){
		for(int i=0;i<g.board.size();i++){
			for(int j=0;j<g.board.size();j++){
				
				if(g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]){
					
					temp = (getValidMoves(g,g.board[i][j]));
					//vector<vector<pair<int,int> > > temp2;
					for(int k=0;k<temp.size();k++){
						
						if(temp[k].size()>1){
							allMoves.push_back(temp[k]);
						}
					}

					
				}
				
				
				temp.clear();
			}
		}
	}

	return allMoves;
}

void Game::humanTurn(int turn){
	// Turn 1: player1
	// Turn 2: player2

	cout<<"Human turn"<<endl;
	
	vector<vector<pair<int,int> > > allMoves = getMoves(turn,currBoard);

	//temp = (getValidMoves(currBoard,currBoard.board[1][5]));
	//allMoves.push_back(temp);

	for(int i=0;i<allMoves.size();i++){
		cout<<i<<"\t";
		for(int j=0;j<allMoves[i].size();j++){
			cout<<" ("<<allMoves[i][j].first<<","<<allMoves[i][j].second<<") --> ";
		}
		cout<<endl;
	}


	int moveNum = -1;
	cout<<"Please make a move: ";

	while(moveNum<0){
		if(allMoves.size()==0){
			(turn==1) ? cout<<currBoard.player1GameReg<<" Loses"<<endl : cout<<currBoard.player2GameReg<<" Loses"<<endl;
			endGame = true;
			return;
		}
		moveNum = inputMove(allMoves);
	}

	cout<<"You chose: "<<moveNum;
	for(int i=0;i<allMoves[moveNum].size();i++){
		cout<<" ("<<allMoves[moveNum][i].first<<","<<allMoves[moveNum][i].second<<") --> ";
	}
	cout<<endl;

	cout<<"Making move...."<<endl;

	currBoard.board = makeMove(currBoard, allMoves[moveNum]);
	printBoard(currBoard);



}

int Game::getHeuristic(Gameboard g, int turn){
	
	string targets[2];
	string enemies[2];

	if(turn==1){
		targets[0] = g.player1GameReg;
		targets[1] = g.player1GameKing;
		enemies[0] = g.player2GameReg;
		enemies[1] = g.player2GameKing;
	} 
	else{
		targets[0] = g.player2GameReg;
		targets[1] = g.player2GameKing;
		enemies[0] = g.player1GameReg;
		enemies[1] = g.player1GameKing;
	}

	// If turn=1, enemyReg=x
	// If turn=-1, enemyReg=0
	//cout<<"Turn: "<<turn<<" EnemyReg: "<<enemies[0]<<endl;

	int numKings = 0;
	int numReg = 0;
	int enemyReg = 0;
	int enemyKing = 0;

	for(int i=0;i<g.board.size();i++){
		for(int j=0;j<g.board[i].size();j++){
			if(g.board[i][j].type==targets[0]){
				numReg++;
			}
			else if(g.board[i][j].type==targets[1]){
				numKings++;
			}
			else if(g.board[i][j].type==enemies[0]){
				enemyReg++;
			}
			else if(g.board[i][j].type==enemies[1]){
				enemyKing++;
			}
		}
	}

	int heur = (4*numKings)+(1*numReg)-(1*enemyReg)-(4*enemyKing);
	//cout<<"PRINTING BOARD"<<endl;
	//cout << "\033[1;31mPrinting Board\033[0m\n";
	//printBoard(g);
	//cout<<"HEURISTIC IS: "<<heur<<endl;

	return heur;
}

int GLOBAL_MOVE_1=-1;

// Pair:
// First - Heuristic
// Second - Moves
int Game::minimax(int depth, Gameboard g, bool maxPlayer, int alpha, int beta,int turn,bool isEven){
	//cout<<"Evaluating at depth: "<<depth<<"Turn is: "<<turn<<endl;
	//Should be 1 and 1
	//cout<<"Turn is: "<<turn<<" Max is: "<<maxPlayer<<endl;
	int MIN = std::numeric_limits<int>::min();
	int MAX = std::numeric_limits<int>::max();

	int correctInd=-1;

	if(depth==0) return getHeuristic(g,turn);

	if(maxPlayer){

		int best = MIN;
		vector<vector<pair<int,int> > > moves = getMoves(turn, g);
		if(moves.size()==0){
			return getHeuristic(g,turn);
		}
		Gameboard tempGame;
		tempGame.board = g.board;
		int superMax;
		if(isEven){
			superMax = MIN;
		}
		else{
			superMax = MAX;
		}
		//int superMax = MAX;
		for(int i=0;i<moves.size();i++){
			tempGame.board = makeMove(g,moves[i]);
			int val;
			if(depth-1%2==0){
				val = minimax(depth-1,tempGame,false,alpha,beta,turn*-1,true);
			}
			else{
				val = minimax(depth-1,tempGame,false,alpha,beta,turn*-1,false);
			}
			//int val = minimax(depth-1,tempGame,false,alpha,beta,turn*-1);

			if(isEven){
				if(val>superMax){
					superMax=val;
					correctInd=i;
				}
			}
			else{
				if(val<superMax){
					superMax=val;
					correctInd=i;
				}
			}

			best = max(best,val);
			alpha = max(alpha,best);
		}

		GLOBAL_MOVE_1 = correctInd;
		return best;
		
	}
	else{

		int best = MAX;
		vector<vector<pair<int,int> > > moves = getMoves(turn, g);
		if(moves.size()==0){
			return getHeuristic(g,turn);
		}
		Gameboard tempGame;
		tempGame.board = g.board;

		for(int i=0;i<moves.size();i++){
			tempGame.board = makeMove(g,moves[i]);
			int val;
			if(depth-1%2==0){
				val = minimax(depth-1,tempGame,true,alpha,beta,turn*-1,true);
			}
			else{
				val = minimax(depth-1,tempGame,true,alpha,beta,turn*-1,false);
			}
			//int val = minimax(depth-1,tempGame,true,alpha,beta,turn*-1);

			best = min(best,val);
			beta = min(beta,best);
			if(beta<=alpha) break;
		}

		return best;

	}

	return 0;
}

int Game::makeMove1(vector<vector<pair<int,int> > > moves, Gameboard g,double secs){
	cout<<"Comp 1 turn"<<endl;
	int MIN = std::numeric_limits<int>::min();
	int MAX = std::numeric_limits<int>::max();

	
	int moveNum = -1;

	Gameboard tempGame;
	tempGame.board = g.board;

	//currBoard.board = makeMove(currBoard, allMoves[moveNum]);

	clock_t start;
	double dur;
	start = clock();

	dur = 0;//(clock()-start)/(double) CLOCKS_PER_SEC;

	int currDepth=0;
	while(dur<(double)secs/2){
		int NUM_DEPTH=currDepth;
		if(NUM_DEPTH%2==0){
			minimax(NUM_DEPTH,g,true,MIN,MAX,1,true);
		}
		else{
			minimax(NUM_DEPTH,g,true,MIN,MAX,1,false);
		}

		moveNum = GLOBAL_MOVE_1;
		
		currDepth++;
		dur = (clock()-start)/(double) CLOCKS_PER_SEC;
	}
	cout<<"Finished searching after: "<<dur<<" seconds and reached depth: "<<currDepth-1<<endl;


	//int moveNum = (rand()%moves.size());
	//return 0;
	return moveNum;
}

int Game::makeMove2(vector<vector<pair<int,int> > > moves, Gameboard g, double secs){
	/*cout<<"Comp 2 turn"<<endl;
	int moveNum = (rand()%moves.size());
	return moveNum;*/

	cout<<"Comp 2 turn"<<endl;
	int MIN = std::numeric_limits<int>::min();
	int MAX = std::numeric_limits<int>::max();

	
	int moveNum = -1;

	Gameboard tempGame;
	tempGame.board = g.board;

	//currBoard.board = makeMove(currBoard, allMoves[moveNum]);

	clock_t start;
	double dur;
	start = clock();

	dur = 0;//(clock()-start)/(double) CLOCKS_PER_SEC;

	int currDepth=0;
	while(dur<(double)secs/2){

		int NUM_DEPTH=currDepth;
		if(NUM_DEPTH%2==0){
			minimax(NUM_DEPTH,g,true,MIN,MAX,-1,true);
		}
		else{
			minimax(NUM_DEPTH,g,true,MIN,MAX,-1,false);
		}
		moveNum = GLOBAL_MOVE_1;

		currDepth++;
		dur = (clock()-start)/(double) CLOCKS_PER_SEC;
	}
	cout<<"Finished searching after: "<<dur<<" seconds and reached depth: "<<currDepth-1<<endl;


	//int moveNum = (rand()%moves.size());
	//return 0;
	return moveNum;
	
}

void Game::compTurn(int turn,double secs){

	// Turn 1: player1
	// Turn 2: player2
	//cout<<"Top left: "<<currBoard.board[0][0].type<<endl;

	cout<<"Computer turn"<<endl;
	vector<vector<pair<int,int> > > allMoves = getMoves(turn,currBoard);

	//temp = (getValidMoves(currBoard,currBoard.board[1][5]));
	//allMoves.push_back(temp);

	for(int i=0;i<allMoves.size();i++){
		cout<<i<<"\t";
		for(int j=0;j<allMoves[i].size();j++){
			cout<<" ("<<allMoves[i][j].first<<","<<allMoves[i][j].second<<") --> ";
		}
		cout<<endl;
	}


	int moveNum = -1;
	cout<<"Computer is making a move...";
	srand(time(0));
	while(moveNum<0){
		//moveNum = inputMove(allMoves);
		if(allMoves.size()==0){
			(turn==1) ? cout<<currBoard.player1GameReg<<" Loses"<<endl : cout<<currBoard.player2GameReg<<" Loses"<<endl;
			endGame = true;
			return;
		}
		if(turn==1){
			moveNum = makeMove1(allMoves,currBoard,secs);
		}
		else{
			//moveNum = makeMove2(allMoves);
			moveNum = makeMove2(allMoves,currBoard,secs);
		}
		//(turn==1) ? moveNum =  makeMove2(allMoves) : moveNum = makeMove1(allMoves,currBoard);
		//moveNum = (rand()%allMoves.size());
	}

	cout<<"Computer chose: "<<moveNum;
	for(int i=0;i<allMoves[moveNum].size();i++){
		cout<<" ("<<allMoves[moveNum][i].first<<","<<allMoves[moveNum][i].second<<") --> ";
	}
	cout<<endl;

	cout<<"Making move...."<<endl;

	currBoard.board = makeMove(currBoard, allMoves[moveNum]);
	printBoard(currBoard);

}

void Game::executeGame(Gameboard g,int whoseTurn, int gameType, double timeLimit){
// gameType = 0: normal (1 comp vs 1 human)
// gameType = 1: (1 comp vs 1 comp)
// gameType = 2: (1 human vs 1 human)

// whoseTurn = 0: Human
// whoseTurn = 1: Comp 
	currBoard = g;
	int num=0;
	int turn;
	(whoseTurn==0) ? turn = 1 : turn = -1;
	cout<<"Turn is: "<<turn<<endl;

	printBoard(g);
	while(!endGame){
		//printBoard(g);

		switch(gameType){
			case 0:
				if(turn>0){
					humanTurn(turn);
				}
				else{
					compTurn(turn,timeLimit);
				}
				turn*=-1;
				break;
			case 1:
				if(turn>0){
					compTurn(turn,timeLimit);
					//sleep(.5);
					usleep(200000);
				}
				else{
					compTurn(turn,timeLimit);
					//sleep(.5);
					usleep(200000);
				}
				turn*=-1;
				break;
			case 2:
				if(turn>0){
					humanTurn(turn);
				}
				else{
					humanTurn(turn);
				}
				turn*=-1;
				break;
		}
		num++;


	}


}










