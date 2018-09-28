
#include <iostream>
#include <vector>
#include <string>
#include "Gameboard.h"

using namespace std;


Gameboard::Gameboard(int size){
	//blankGame = " - ";
	//player1Game = " X ";
	//player2Game = " O ";
	//types[5] = {{" - "," x "," o "," X "," O "}};

	blankGame = " - ";
	player1GameReg = " o ";
	player2GameReg = " x ";
	player1GameKing = " O ";
	player2GameKing = " X ";

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

Gameboard::Square::Square(string t ,int i,int j){

	type = t;
	isKing = false;
	coords = make_pair(i,j);
	

}







