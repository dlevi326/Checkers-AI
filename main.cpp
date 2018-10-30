#include <iostream>
#include <vector>
#include <fstream>

#include "Game.h"
#include "Gameboard.h"

using namespace std;

int makeChoiceMode(){
	int num = -1;
	cin>>num;
	if(!cin){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Invalid game mode, please choose again: ";
		return -1;
	}
	if(num != 0 && num != 1 && num != 2){
		cout<<"Invalid game mode, please choose again: ";
		return -1;
	}
	else{
		return num;
	}
	return -1;
}

inline bool exists(const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

string makeChoiceBoard(){
	string ans = "";
	cin>>ans;
	if(!cin){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Invalid choice, please choose again: ";
		return "";
	}
	if(ans != "y" && ans != "n"){
		cout<<"Invalid choice, please choose again: ";
		return "";
	}
	else{
		return ans;
	}
	return "";
}

string makeChoiceFile(){
	string ans = "";
	cin>>ans;
	if(!cin){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Invalid choice, please choose again: ";
		return "";
	}
	if(!exists(ans)){
		cout<<"File does not exist, please choose again: ";
		return "";
	}
	else{
		return ans;
	}
	return "";
}

int makeChoiceTurn(){
	int num = -1;
	cin>>num;
	if(!cin){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Invalid turn, please choose again: ";
		return -1;
	}
	if(num != 0 && num != 1){
		cout<<"Invalid turn, please choose again: ";
		return -1;
	}
	else{
		return num;
	}
	return -1;
}

double makeChoiceTime(){
	double num = -1;
	cin>>num;
	if(!cin){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Invalid time limit, please choose again: ";
		return -1;
	}
	if(num<0){
		cout<<"Invalid time limit, please choose again: ";
		return -1;
	}
	else if(num<.1){
		cout<<"Time must be greater than .1 seconds, please choose again: ";
		return -1;
	}
	else{
		return num;
	}
	return -1;
}

int main(){
	cout<<"Welcome to checkers, please select one of the following game modes:"<<endl;
	cout<<"(0) 1 Computer vs 1 Human"<<endl;
	cout<<"(1) 1 Computer vs 1 Computer"<<endl;
	cout<<"(2) 1 Human vs 1 Human"<<endl;
	cout<<"Please make selection: ";

	int mode = -1;
	while(mode<0){
		mode = makeChoiceMode();
	}

	int turn = 1;
	if(mode==0){
		cout<<"Who would you like to start:"<<endl;
		cout<<"(0) Human Start"<<endl;
		cout<<"(1) Computer start"<<endl;
		cout<<"Please make selection: ";

		turn = -1;
		while(turn<0){
			turn = makeChoiceTurn();
		}
	}
	
	cout<<"Thank you, would you like to load an existing board (y/n)? ";
	string choice;
	while(choice==""){
		choice = makeChoiceBoard();
	}
	string boardFile = "";
	if(choice=="y"){
		cout<<"Please choose file: ";
		while(boardFile==""){
			boardFile = makeChoiceFile();
		}
	}
	else{
		boardFile = "pracBoards/mainBoard.txt";
	}

	cout<<"Finally please input time limit in seconds: ";
	double limit = -1;
	while(limit<0){
		limit = makeChoiceTime();
	}

	Game g;
	Gameboard game;

	game.load_board(game,boardFile);

	g.executeGame(game,turn,mode,limit);









	return 0;
}
