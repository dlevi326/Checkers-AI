#include <iostream>
#include <vector>

#include "Game.h"
#include "Gameboard.h"

using namespace std;

int main(){

	Game g;
	Gameboard game;

	game.load_board(game,"pracBoards/board2.txt");

	g.executeGame(game);









	return 0;
}
