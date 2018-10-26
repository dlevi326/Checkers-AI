
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Gameboard.h"

using namespace std;

int defArray[8][8] = {{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1}};

Gameboard::Gameboard(int size){
	//blankGame = " - ";
	//player1Game = " X ";
	//player2Game = " O ";
	//types[5] = {{" - "," x "," o "," X "," O "}};


	blankGame = " - ";
	player1GameReg = " o "; // o
	player2GameReg = " x "; // x
	player1GameKing = " 0 "; // O
	player2GameKing = " Z "; // X

	string blank = blankGame;
	string player1 = player1GameKing;
	string player2 = player2GameKing;


	string arr[8][8] = {{player1,blank,player1,blank,player1,blank,player1,blank},{blank,player1,blank,player1,blank,player1,blank,player1},{player1,blank,player1,blank,player1,blank,player1,blank},
		{blank,blank,blank,blank,blank,blank,blank,blank},{blank,blank,blank,blank,blank,blank,blank,blank},
		{blank,player2,blank,player2,blank,player2,blank,player2},{player2,blank,player2,blank,player2,blank,player2,blank},{blank,player2,blank,player2,blank,player2,blank,player2}};



	for(int i=0;i<size;i++){
		vector<Square> v;
		for(int j=0;j<size;j++){
			Square s(arr[i][j],i,j);
			if(arr[i][j]==player1GameKing || arr[i][j]==player2GameKing){
				s.isKing = true;
			}
			else{
				s.isKing = false;
			}
			v.push_back(s);
		}
		board.push_back(v);
	}

}

void Gameboard::load_board(Gameboard& g,string file){
	ifstream inFile;
	inFile.open(file);

	if (!inFile) {
	    cerr << "Unable to open file datafile.txt";
	    exit(1);   // call system to stop
	}

	string line;
	string x;
	int ind1=0;
	int ind2=0;
	while ( getline (inFile,line) )
    {
    	for(int i=0;i<line.length();i++){
    		int num = (int) line[i]- '0';
    		//ind1 = 0;
    		//ind2 = 0;
    		switch(num){
    		case 0:
    			g.board[ind1][ind2].type = g.blankGame;
    			g.board[ind1][ind2].isKing = false;
    			ind2++;
    			break;
    		case 1:
    			g.board[ind1][ind2].type = g.player1GameReg;
    			g.board[ind1][ind2].isKing = false;
    			ind2++;
    			break;
    		case 2:
    			g.board[ind1][ind2].type = g.player1GameKing;
    			g.board[ind1][ind2].isKing = true;
    			ind2++;
    			break;
    		case 3:
    			g.board[ind1][ind2].type = g.player2GameReg;
    			g.board[ind1][ind2].isKing = false;
    			ind2++;
    			break;
    		case 4:
    			g.board[ind1][ind2].type = g.player2GameKing;
    			g.board[ind1][ind2].isKing = true;
    			ind2++;
    			break;
    		default:
    			continue;
    		}

    	}
    	ind2 = 0;
    	ind1++;
      //cout << line << '\n';
    }
    inFile.close();

    /*for(int i=0;i<8;i++){
    	for(int j=0;j<8;j++){
    		cout<<g.board[i][j].type;
    	}
    	cout<<endl;
    }*/

}

Gameboard::Square::Square(string t ,int i,int j){

	type = t;
	isKing = false;
	coords = make_pair(i,j);
	

}







