#ifndef __GAMEBOARD_h__
#define __GAMEBOARD_h__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Gameboard{
public:

	class Square{
	public:
		string type;

		bool isKing;
		pair<int,int> coords;

		Square(string t,int i,int j);
	};

	//string types[5];
	//string blankGame;
	//string player1Game;
	//string player2Game;

	string blankGame;
	string player1GameReg;
	string player2GameReg;
	string player1GameKing;
	string player2GameKing;
	vector<vector<Square> > board;





	Gameboard(int size=8);

	void load_board(Gameboard& ,string);

};







#endif