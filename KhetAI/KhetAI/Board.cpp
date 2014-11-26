#include "Board.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/* 
 Author: Josh Walton
 Course: COMP 445, AI
 Date: 18 November 2014	
 Description: defines the khetboard object, used to store a khetboard
*/

enum icon {
	Empty=176,
	Wall=219,
	Laser=206,
	King=15,
	Blocker=30,
	MirrorLU=217,		//CONVENTION: THE TWO DIRECTION LETTERS INDICATE WHICH SIDE REFLECTS LASER
	MirrorLD=191,
	MirrorRU=192,
	MirrorRD=218,
	DMirrorFSlash=47,	/*	MIRROR LOOKA LIKA DIS:		 /					*/
	DMirrorBSlash=92,	/*	MIRROR LOOKA LIKA DIS:		 \					*/
};

Board::Board() {
	for(int i=0; i<10; i++){
		for(int j=0; j<12; j++){
			board[i][j] = new Piece();
		}
	}
};

Board::Board(string file) {
	fstream fin;
	char temp;
	fin.open(file + ".txt");

	for(int i=0; i<10; i++){
		for(int j=0; j<12; j++){
			fin >> temp;
			switch(temp) {
				case '_': board[i][j] = new Piece(0,(char)Empty);				break;
				case 'W': board[i][j] = new Piece(0,(char)Wall);				break;
				case 'L': board[i][j] = new Piece(0,(char)Laser);				break;
				case 'B': board[i][j] = new Piece(0,(char)Blocker);				break;
				case 'K': board[i][j] = new Piece(0,(char)King);				break;
				case '1': board[i][j] = new Piece(0,(char)MirrorLD);			break;
				case '2': board[i][j] = new Piece(0,(char)MirrorLU);			break;
				case '3': board[i][j] = new Piece(0,(char)MirrorRU);			break;
				case '4': board[i][j] = new Piece(0,(char)MirrorRD);			break;
				case '5': board[i][j] = new Piece(0,(char)DMirrorFSlash);		break;
				case '6': board[i][j] = new Piece(0,(char)DMirrorBSlash);		break;
			}
		}
		fin.get();
	}

	for(int i=0; i<10; i++){
		for(int j=0; j<12; j++){
			fin >> temp;
			board[i][j]->setOwner((int)temp - 48);
		}
		fin.get();
	}
}

//Outputs the screen to the console
void Board::PrintBoard() {
	for(int i=0; i<10; i++){
		for(int j=0; j<12; j++){
			cout << board[i][j]->getIcon() << " ";
		}
		cout << endl << endl;
	}
}

//Hoo boy
Impact Board::TraceLaser(int player) {



}