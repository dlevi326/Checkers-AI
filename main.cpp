#include <iostream>
#include <vector>

#include "Game.h"
#include "Gameboard.h"

using namespace std;

int main(){

	Game g;
	Gameboard game;

	game.load_board(game,"pracBoards/boardWrong2.txt");

	int gameMode = 1;
	int turn = 1;
	g.executeGame(game,turn,gameMode);









	return 0;
}
