// TODO:
// Still need to add: Timing, AB pruning (I think i need to fix AB)

// maybe i shouldnt sacrifice a piece to get a king

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

	//cout<<"ANALYZING PIECE AT: "<<s.coords.first<<","<<s.coords.second<<endl;
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

double Game::getHeuristic1(Gameboard g, int turn,int depth){
	//return getHeuristic2(g,turn,depth);
	//turn*=-1;
	return getHeuristic(g,turn,depth);
	
	string targets[2];
	string enemies[2];

	int back;
	if(turn==1){
		targets[0] = g.player1GameReg;
		targets[1] = g.player1GameKing;
		enemies[0] = g.player2GameReg;
		enemies[1] = g.player2GameKing;
		back=0;
	} 
	else{
		targets[0] = g.player2GameReg;
		targets[1] = g.player2GameKing;
		enemies[0] = g.player1GameReg;
		enemies[1] = g.player1GameKing;
		back=7;
	}

	int numKings = 0;
	int numReg = 0;
	int enemyReg = 0;
	int enemyKing = 0;
	int numBack = 0;
	int numSide=0;
	int numMiddle=0;
	int targGuard=0;
	int enemyGuard=0;

	for(int i=0;i<g.board.size();i++){
		for(int j=0;j<g.board[i].size();j++){
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && i==back){
				numBack++;
			}
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && (j==0 || j==7)){
				numSide++;
			}
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && ((i==3&&j==3)||(i==3&&j==4)||(i==4&&j==3)||(i==4&&j==4))){
				numMiddle++;
			}
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
			
			if(j!=0 && j!=7 && i!=0 && i!=7){
				if(g.board[i][j].type==enemies[0] || g.board[i][j].type==enemies[1]){
					if(g.board[i+1][j+1].type==enemies[0] || g.board[i+1][j+1].type==enemies[1]){
						enemyGuard++;
					}
					if(g.board[i-1][j+1].type==enemies[0] || g.board[i-1][j+1].type==enemies[1]){
						enemyGuard++;
					}
					if(g.board[i-1][j-1].type==enemies[0] || g.board[i-1][j-1].type==enemies[1]){
						enemyGuard++;
					}
					if(g.board[i+1][j-1].type==enemies[0] || g.board[i+1][j-1].type==enemies[1]){
						enemyGuard++;
					}

					if(g.board[i+1][j+1].type==targets[0] || g.board[i+1][j+1].type==targets[1]){
						targGuard++;
					}
					if(g.board[i-1][j+1].type==targets[0] || g.board[i-1][j+1].type==targets[1]){
						targGuard++;
					}
					if(g.board[i-1][j-1].type==targets[0] || g.board[i-1][j-1].type==targets[1]){
						targGuard++;
					}
					if(g.board[i+1][j-1].type==targets[0] || g.board[i+1][j-1].type==targets[1]){
						targGuard++;
					}
				}
			}
		}
	}

	int otherScore=0;
	if(numReg+numKings==0){
		otherScore-=10000;
	}
	if(enemyReg+enemyKing==0){
		otherScore+=10000;
	}

	int valEnemyKing;
	int valEnemyReg;
	int valTargKing;
	int valTargReg;
	valEnemyKing = 1500;//800;//1700;
	valEnemyReg = 1000;//500;//900;
	valTargKing = 1500;
	valTargReg = 1000;

	double heur = (valTargKing*numKings)+(valTargReg*numReg)-(valEnemyReg*enemyReg)-(valEnemyKing*enemyKing)-depth+(10*numBack)+(.1*numSide)+(10*numMiddle)-(2*enemyGuard)+(2*targGuard)+otherScore;
	
	//cout<<"HEURISTIC: "<<heur<<endl;
	//cout<<"----------------"<<endl;
	//cout<<"NUM SIDE: "<<numSide<<endl;
	//cout<<"NUM MIDDLE: "<<numMiddle<<endl;
	//cout<<"NUM ENEMY GUARD: "<<enemyGuard<<endl;
	/*cout<<"PRINTING BOARD"<<endl;
	cout << "\033[1;31mPrinting Board\033[0m\n";
	printBoard(g);
	cout<<"HEURISTIC IS: "<<heur<<endl;
	cout<<"NUM OWN KINGS: "<<numKings<<endl;
	cout<<"NUM OWN REG: "<<numReg<<endl;
	cout<<"NUM ENEMY KINGS: "<<enemyKing<<endl;
	cout<<"NUM ENEMY REG: "<<enemyReg<<endl;*/


	return heur;
	//return getHeuristic(g,turn);
}

double Game::getHeuristic2(Gameboard g, int turn, int depth){

	return getHeuristic(g,turn,depth);
	
	string targets[2];
	string enemies[2];

	int back;
	if(turn==1){
		targets[0] = g.player1GameReg;
		targets[1] = g.player1GameKing;
		enemies[0] = g.player2GameReg;
		enemies[1] = g.player2GameKing;
		back=0;
	} 
	else{
		targets[0] = g.player2GameReg;
		targets[1] = g.player2GameKing;
		enemies[0] = g.player1GameReg;
		enemies[1] = g.player1GameKing;
		back=7;
	}

	int numKings = 0;
	int numReg = 0;
	int enemyReg = 0;
	int enemyKing = 0;
	int numBack = 0;
	int numSide=0;
	int numMiddle=0;

	for(int i=0;i<g.board.size();i++){
		for(int j=0;j<g.board[i].size();j++){
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && i==back){
				numBack++;
			}
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && (j==0 || j==7)){
				numSide++;
			}
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && ((i==3&&j==3)||(i==3&&j==4)||(i==4&&j==3)||(i==4&&j==4))){
				numMiddle++;
			}
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

	int otherScore=0;
	if(numReg+numKings==0){
		otherScore-=10000;
	}
	if(enemyReg+enemyKing==0){
		otherScore+=10000;
	}

	int valEnemyKing;
	int valEnemyReg;
	int valTargKing;
	int valTargReg;
	if(numKings+numReg>enemyReg+enemyKing){
		valEnemyKing = 500;//800;//1900;
		valEnemyReg = 250;//500;//1100;
		valTargKing = 1500;
		valTargReg = 1000;
	}
	else{
		valEnemyKing = 500;//800;//1700;
		valEnemyReg = 250;//500;//900;
		valTargKing = 1500;
		valTargReg = 1000;
	}

	double heur = (valTargKing*numKings)+(valTargReg*numReg)-(valEnemyReg*enemyReg)-(valEnemyKing*enemyKing)-depth+(10*numBack)+(2*numSide)+(10*numMiddle)+otherScore;
	//cout<<"PRINTING BOARD"<<endl;
	//cout << "\033[1;31mPrinting Board\033[0m\n";
	//printBoard(g);
	/*cout<<"HEURISTIC IS: "<<heur<<endl;
	cout<<"NUM OWN KINGS: "<<numKings<<endl;
	cout<<"NUM OWN REG: "<<numReg<<endl;
	cout<<"NUM ENEMY KINGS: "<<enemyKing<<endl;
	cout<<"NUM ENEMY REG: "<<enemyReg<<endl;*/


	return heur;


}

double Game::getHeuristic(Gameboard g, int turn, int depth){

	string targets[2];
	string enemies[2];

	int backTarg;
	int backEnemy;
	if(turn==1){
		targets[0] = g.player1GameReg;
		targets[1] = g.player1GameKing;
		enemies[0] = g.player2GameReg;
		enemies[1] = g.player2GameKing;
		backTarg=0;
		backEnemy=7;
	} 
	else{
		targets[0] = g.player2GameReg;
		targets[1] = g.player2GameKing;
		enemies[0] = g.player1GameReg;
		enemies[1] = g.player1GameKing;
		backTarg=7;
		backEnemy=0;
	}

	int numKings = 0;
	int numReg = 0;
	int enemyReg = 0;
	int enemyKing = 0;
	int numBackTarg = 0;
	int numBackEnemy = 0;
	int numSideTarg=0;
	int numSideEnemy=0;
	int numMiddleTarg=0;
	int numMiddleEnemy=0;
	int targGuard=0;
	int enemyGuard=0;

	for(int i=0;i<g.board.size();i++){
		for(int j=0;j<g.board[i].size();j++){
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && i==backTarg){
				numBackTarg++;
			}
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && (j==0 || j==7)){
				numSideTarg++;
			}
			if((g.board[i][j].type==targets[0] || g.board[i][j].type==targets[1]) && ((i==3&&j==3)||(i==3&&j==4)||(i==4&&j==3)||(i==4&&j==4))){
				numMiddleTarg++;
			}

			if((g.board[i][j].type==enemies[0] || g.board[i][j].type==enemies[1]) && i==backEnemy){
				numBackTarg++;
			}
			if((g.board[i][j].type==enemies[0] || g.board[i][j].type==enemies[1]) && (j==0 || j==7)){
				numSideTarg++;
			}
			if((g.board[i][j].type==enemies[0] || g.board[i][j].type==enemies[1]) && ((i==3&&j==3)||(i==3&&j==4)||(i==4&&j==3)||(i==4&&j==4))){
				numMiddleTarg++;
			}

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
			
			if(j!=0 && j!=7 && i!=0 && i!=7){
				if(g.board[i][j].type==enemies[0] || g.board[i][j].type==enemies[1]){
					if(g.board[i+1][j+1].type==enemies[0] || g.board[i+1][j+1].type==enemies[1]){
						enemyGuard++;
					}
					if(g.board[i-1][j+1].type==enemies[0] || g.board[i-1][j+1].type==enemies[1]){
						enemyGuard++;
					}
					if(g.board[i-1][j-1].type==enemies[0] || g.board[i-1][j-1].type==enemies[1]){
						enemyGuard++;
					}
					if(g.board[i+1][j-1].type==enemies[0] || g.board[i+1][j-1].type==enemies[1]){
						enemyGuard++;
					}

					if(g.board[i+1][j+1].type==targets[0] || g.board[i+1][j+1].type==targets[1]){
						targGuard++;
					}
					if(g.board[i-1][j+1].type==targets[0] || g.board[i-1][j+1].type==targets[1]){
						targGuard++;
					}
					if(g.board[i-1][j-1].type==targets[0] || g.board[i-1][j-1].type==targets[1]){
						targGuard++;
					}
					if(g.board[i+1][j-1].type==targets[0] || g.board[i+1][j-1].type==targets[1]){
						targGuard++;
					}
				}
			}
		}
	}

	int otherScore=0;
	if(numReg+numKings==0){
		otherScore-=10000;
	}
	if(enemyReg+enemyKing==0){
		otherScore+=10000;
	}

	int valEnemyKing;
	int valEnemyReg;
	int valTargKing;
	int valTargReg;
	valEnemyKing = 1500;//800;//1700;
	valEnemyReg = 1000;//500;//900;
	valTargKing = 1500;
	valTargReg = 1000;

	double heur = (valTargKing*numKings)+(valTargReg*numReg)-(valEnemyReg*enemyReg)-(valEnemyKing*enemyKing)-depth+(10*numBackTarg)+(.1*numSideTarg)+(10*numMiddleTarg)-(10*numBackEnemy)-(.1*numSideEnemy)-(10*numMiddleEnemy)-(2*enemyGuard)+(2*targGuard)+otherScore;
	
	//cout<<"HEURISTIC: "<<heur<<endl;
	//cout<<"----------------"<<endl;
	//cout<<"NUM SIDE: "<<numSide<<endl;
	//cout<<"NUM MIDDLE: "<<numMiddle<<endl;
	//cout<<"NUM ENEMY GUARD: "<<enemyGuard<<endl;
	/*cout<<"PRINTING BOARD"<<endl;
	cout << "\033[1;31mPrinting Board\033[0m\n";
	printBoard(g);
	cout<<"HEURISTIC IS: "<<heur<<endl;
	cout<<"NUM OWN KINGS: "<<numKings<<endl;
	cout<<"NUM OWN REG: "<<numReg<<endl;
	cout<<"NUM ENEMY KINGS: "<<enemyKing<<endl;
	cout<<"NUM ENEMY REG: "<<enemyReg<<endl;*/


	return heur;
}

void printMoves(vector<vector<pair<int,int> > > p){
	cout<<"-------------------\n----------------\n----------------------\n------------";
	for(int i=0;i<p.size();i++){
		for(int j=0;j<p[i].size();j++){
			cout<<"("<<p[i][j].first<<","<<p[i][j].second<<") --> ";
		}
		cout<<"\n\t\t||||\n";
	}
}

int GLOBAL_MOVE_1=-1;
bool setGlobal=true;

// Pair:
// First - Heuristic
// Second - Moves
double Game::minimax(int depth,int maxDepth, Gameboard g, bool maxPlayer, int alpha, int beta,int turn,bool isEven,bool isPlayer1,double start,double timeLimit,vector<vector<pair<int,int> > > path){
	//cout<<"Evaluating at depth: "<<depth<<"Turn is: "<<turn<<endl;
	//Should be 1 and 1
	//cout<<"Turn is: "<<turn<<" Max is: "<<maxPlayer<<endl;
	//isEven=false;

	vector<vector<pair<int,int> > > bestPath;
	int MIN = std::numeric_limits<int>::min();
	int MAX = std::numeric_limits<int>::max();

	vector<int> bestInds;

	int correctInd=-1;

	double dur = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
	if(dur>=(timeLimit-.1)){
		//cout<<"Breaking in middle of minimax!!!"<<endl;
		//cout<<"Dur is: "<<dur<<" with a timeLimit of: "<<timeLimit<<endl;
		setGlobal=false;
		return -1;
	}

	if(depth==0){
		if(isPlayer1){
			//cout<<"GETTING HEURISTIC FOR DEPTH: "<<depth<<endl;
			//printMoves(path);
			return getHeuristic1(g,turn,depth);
		}
		else{
			return getHeuristic2(g,turn,depth);
		}
	} 

	if(maxPlayer){

		double best = MIN;
		vector<vector<pair<int,int> > > moves = getMoves(turn, g);
		if(moves.size()==0){
			if(isPlayer1){
				return getHeuristic1(g,turn,depth);
			}
			else{
				return getHeuristic2(g,turn,depth);
			}
		}
		Gameboard tempGame;
		tempGame.board = g.board;
		
		for(int i=0;i<moves.size();i++){
			/*if(depth==maxDepth){
				cout<<"Currently evaluating move: "<<i<<" with total depth: "<<maxDepth<<endl;
			}*/
			tempGame.board = makeMove(g,moves[i]);
			double val;

			path.push_back(moves[i]);
			val = minimax(depth-1,maxDepth,tempGame,false,alpha,beta,turn,true,isPlayer1,start,timeLimit,path);
			if(depth==maxDepth){
				//cout<<"HEURISTIC IS: "<<val<<endl;
				//cout<<"FOR MOVE: "<<i<<" at depth: "<<maxDepth<<endl;
			}
			//best = max(best,val);
			//alpha = max(alpha,best);
			if(val>best){
				best = val;
				alpha = best;
				correctInd=i;
				bestInds.clear();
				bestInds.push_back(i);
			}
			else if(val==best){
				bestInds.push_back(i);
			}

			if(beta<=alpha){
				break;
			}	

		}

		if(depth==maxDepth){
			//cout<<"Best move tied with: "<<bestInds.size()<<" others"<<endl;
		}

		if(depth==maxDepth){
			//cout<<"-------------------------------"<<endl;
			//cout<<"Setting global move!!!!"<<endl;
			GLOBAL_MOVE_1 = bestInds[(rand()%bestInds.size())];
		}
		if(depth==maxDepth){
			//cout<<"HEURISTIC IS: "<<best<<endl;
			//cout<<"GLOBAL MOVE IS: "<<GLOBAL_MOVE_1<<endl;
			//cout<<"BEST MOVE TIED WITH: "<<bestInds.size()<<endl;
		}
		return best;
		
	}
	else{

		double best = MAX;
		vector<vector<pair<int,int> > > moves = getMoves(turn*-1, g);
		if(moves.size()==0){
			if(isPlayer1){
				return getHeuristic1(g,turn,depth);
			}
			else{
				return getHeuristic2(g,turn,depth);
			}
		}
		Gameboard tempGame;
		tempGame.board = g.board;

		for(int i=0;i<moves.size();i++){
			tempGame.board = makeMove(g,moves[i]);
			double val;
			path.push_back(moves[i]);
			if(depth-1%2==0){
				val = minimax(depth-1,maxDepth,tempGame,true,alpha,beta,turn,true,isPlayer1,start,timeLimit,path);
			}
			else{
				val = minimax(depth-1,maxDepth,tempGame,true,alpha,beta,turn,false,isPlayer1,start,timeLimit,path);
			}
			

			//best = min(best,val);
			//beta = min(beta,best);

			if(val<best){
				best = val;
				beta = best;
			}
			if(beta<=alpha){
				break;
			}
		}

		return best;

	}

	return -1;
}

int Game::makeMove1(vector<vector<pair<int,int> > > moves, Gameboard g,double secs){
	cout<<"Comp 1 turn"<<endl;
	int MIN = std::numeric_limits<int>::min();
	int MAX = std::numeric_limits<int>::max();
	//cout<<MIN<<endl;
	//cout<<MAX<<endl;

	if(getMoves(1, g).size()==1){
		return 0;
	}
	
	int moveNum = -1;

	Gameboard tempGame;
	tempGame.board = g.board;

	//currBoard.board = makeMove(currBoard, allMoves[moveNum]);

	clock_t start;
	double dur;
	start = clock();

	dur = 0;//(clock()-start)/(double) CLOCKS_PER_SEC;
	vector<vector<pair<int,int> > > path;
	int currDepth=1;
	double curHeur = (double)MIN;
	double maxHeur = (double)MIN;
	int maxMove = -1;
	while(dur<(double)secs-.1){

		// TEST
		int NUM_DEPTH = currDepth;//2;//4;
		//int NUM_DEPTH=currDepth;

		curHeur = minimax(NUM_DEPTH,NUM_DEPTH,g,true,MIN,MAX,1,false,true,start,secs,path);
		if(setGlobal){
			if(curHeur!=maxHeur){
				maxHeur=curHeur;
				maxMove = GLOBAL_MOVE_1;
			}
		}
		else{
			setGlobal=true;
		}

		/*if(setGlobal){
			moveNum = GLOBAL_MOVE_1;	
		}
		else{
			setGlobal=true;
			//break;
		}*/
		
		currDepth++;
		dur = (double)(clock()-start)/(double) CLOCKS_PER_SEC;

		// TEST
		//break;
	}
	cout<<"Finished searching after: "<<dur<<" seconds and reached depth: "<<currDepth-1<<endl;
	cout<<"Max heuristic was: "<<maxHeur<<" max move is: "<<maxMove<<endl;


	//int moveNum = (rand()%moves.size());
	//return 0;
	return maxMove;
	return moveNum;
}

int Game::makeMove2(vector<vector<pair<int,int> > > moves, Gameboard g, double secs){
	/*cout<<"Comp 2 turn"<<endl;
	int moveNum = (rand()%moves.size());
	return moveNum;*/

	if(getMoves(-1, g).size()==1){
		return 0;
	}

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

	vector<vector<pair<int,int> > > path;
	int currDepth=1;
	double curHeur=(double)MIN;
	double maxHeur=(double)MIN;
	int maxMove=-1;
	while(dur<(double)secs-.1){
		int NUM_DEPTH=currDepth;

		curHeur = minimax(NUM_DEPTH,NUM_DEPTH,g,true,MIN,MAX,-1,false,false,start,secs,path);
		if(setGlobal){
			if(curHeur!=maxHeur){
				maxHeur=curHeur;
				maxMove = GLOBAL_MOVE_1;
			}
		}
		else{
			setGlobal=true;
		}

		/*if(setGlobal){
			moveNum = GLOBAL_MOVE_1;
		}
		else{
			setGlobal=true;
		}*/

		currDepth++;
		dur = (double)(clock()-start)/(double) CLOCKS_PER_SEC;
	}
	cout<<"Finished searching after: "<<dur<<" seconds and reached depth: "<<currDepth-1<<endl;
	cout<<"Max heuristic was: "<<maxHeur<<" max move is: "<<maxMove<<endl;


	//int moveNum = (rand()%moves.size());
	//return 0;
	return maxMove;
	return moveNum;
	
}

void Game::compTurn(int turn,double secs){

	// Turn 1: player1
	// Turn 2: player2
	//cout<<"Top left: "<<currBoard.board[0][0].type<<endl;

	cout<<"Computer turn: "<<turn<<endl;
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

void Game::executeGame(Gameboard g,int whoseTurn, int gameType, double timeLimit, int player){
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
				if(player==1){
					turn*=-1;
					// if(turn<0)
					if(turn<0){
						humanTurn(turn);
					}
					else{
						compTurn(turn,timeLimit);
					}
				}
				else{
					if(turn>0){
						humanTurn(turn);
					}
					else{
						compTurn(turn,timeLimit);
					}
					turn*=-1;
				}
				/*turn*=-1;
				// if(turn<0)
				if(turn<0){
					humanTurn(turn);
				}
				else{
					compTurn(turn,timeLimit);
				}*/
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










