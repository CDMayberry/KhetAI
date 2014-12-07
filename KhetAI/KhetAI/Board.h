#ifndef KHETBOARD_H
#define KHETBOARD_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Piece.h"
#include "Impact.h"
using namespace std;

/* 
 Author: Josh Walton
 Course: COMP 445, AI
 Date: 18 November 2014	
 Description: defines the khetboard object, used to store a khetboard
*/

enum Move {
	RotateLeft,
	RotateRight,
	MoveUp,
	MoveUpRight,
	MoveRight,
	MoveDownRight,
	MoveDown,
	MoveDownLeft,
	MoveLeft,
	MoveUpLeft,
};

class Play{
public:
	Play(){
		//default does nothing for now
	}
	Play(int x, int y, int pType, int moveORturnDirection){
		xPosition = x;
		yPosition = y;
		playType = pType;
		if(pType == MOVE){
			moveDir = moveORturnDirection;
		}else if(pType == TURN){
			turnDir = moveORturnDirection;
		}
	}
	static enum play_type{MOVE, TURN};
	static enum move_directions{UP, UP_RIGHT, RIGHT, RIGHT_DOWN, DOWN, DOWN_LEFT, LEFT, LEFT_UP};
	static enum turn_directions{CLOCKWISE, COUNTERCLOCKWISE};
private:
	int playType; //0 for move, 1 for turn
	int moveDir;
	int turnDir;
	int xPosition, yPosition;
};

class Board{
public:
//Constructors
	//Default
	Board();
	//Takes a file name as a string and creates a board object from it
	Board(string file);

//Accessors
	//Outputs the screen to the console
	void PrintBoard();
	//Traces the laser of the given player and returns an impact object
	Impact TraceLaser(int player);
	//returns a vector of possible plays for a given player
	vector<Play> listAllPlays(int player);
	//returns a version of the world after making a play
	Board makePlay(Play p){
			//apply the play to the board
		//TODO
	}

//Mutators
	//Reads the data from a file 
	void readBoard(string f){
		filename = f;
		fin.open(filename);

		char tempChar;
		for(int i=0; i<10; i++){
			for(int j=0; j<12; j++){
				fin >> tempChar;
				board[i][j]->setIcon(tempChar);
			}
		}
		int tempInt;
		for(int i=0; i<10; i++){
			for(int j=0; j<12; j++){
				fin >> tempInt;
				board[i][j]->setOwner(tempInt);
			}
		}
	}



private:
	//Array of pieces, going x by y
	Piece* board[10][12];
	string filename;
	ifstream fin;
	ofstream fout;
};

#endif