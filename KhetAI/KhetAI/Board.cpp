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
	Empty=0,
	Wall=219,
	Laser=206,
	King=15,
	Blocker=30,
	MirrorLU=217,		//CONVENTION: THE TWO DIRECTION LETTERS INDICATE WHICH SIDE REFLECTS LASER
	MirrorLD=191,
	MirrorRU=192,
	MirrorRD=218,
	DMirrorFSlash=47,	/*	MIRROR LOOKA LIKEA DIS: /	*/
	DMirrorBSlash=92,	/*	MIRROR LOOKA LIKEA DIS: \	*/
};

Board::Board() {};

Board::Board(string file) {
	fstream fin;
	char temp;
	fin.open(file + ".txt");
	for(int i=0; i<12; i++){
		for(int j=0; j<10; j++){
			fin.get(temp);
			switch(temp) {
				case ' ': board[i][j].setIcon((char)Empty); break;
				case 'W': board[i][j].setIcon((char)Wall); break;
				case 'L': board[i][j].setIcon((char)Laser); break;
				case 'B': board[i][j].setIcon((char)Blocker); break;
				case 'K': board[i][j].setIcon((char)King); break;
				case '1': board[i][j].setIcon((char)MirrorLD); break;
				case '2': board[i][j].setIcon((char)MirrorLU); break;
				case '3': board[i][j].setIcon((char)MirrorRU); break;
				case '4': board[i][j].setIcon((char)MirrorRD); break;
				case '5': board[i][j].setIcon((char)DMirrorFSlash); break;
				case '6': board[i][j].setIcon((char)DMirrorBSlash); break;
			}
		}
		fin.get();
	}
	for(int i=0; i<12; i++){
		for(int j=0; j<10; j++){
			fin.get(temp);
			board[i][j].setOwner((int)temp-48);
		}
		fin.get();
	}
}