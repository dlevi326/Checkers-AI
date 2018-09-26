#ifndef __SQUARE_h__
#define __SQUARE_h__

#include <iostream>

using namespace std;

class Square{

public:

	string type;
	bool isKing;
	pair<int,int> coords;

	Square(string t,int i,int j);

};

Square::Square(string t,int i,int j){

	type = t;
	isKing = false;
	coords = make_pair(i,j);

}







#endif