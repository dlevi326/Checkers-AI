
#include <iostream>
#include <vector>
#include "Square.h"

using namespace std;





Gameboard::Gameboard(int size){
	string blank = "\t";
	string player1 = " X ";
	string player2 = " O ";

	string arr[8][8] = {{player1,blank,player1,blank,player1,blank,player1,blank},{blank,player1,blank,player1,blank,player1,blank,player1},{player1,blank,player1,blank,player1,blank,player1,blank},
					{blank,blank,blank,blank,blank,blank,blank,blank},{blank,blank,blank,blank,blank,blank,blank,blank},
					{blank,player2,blank,player2,blank,player2,blank,player2},{player2,blank,player2,blank,player2,blank,player2,blank},{blank,player2,blank,player2,blank,player2,blank,player2}};

	for(int i=0;i<size;i++){
		vector<Square> v;
		for(int j=0;j<size;j++){
			Square s(arr[i][j],i,j);
			v.push_back(s);
		}
		board.push_back(v);
	}
}







