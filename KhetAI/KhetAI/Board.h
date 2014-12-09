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
	bool operator==(Play p){
		if(xPosition == p.xPosition &&
			yPosition == p.yPosition &&
			(moveDir == p.moveDir || turnDir == p.turnDir) &&
			playType == p.playType){
			return true;
		}
		return false;
	}

	bool operator==(int type) {
		if(playType == type) {
			return true;
		}
		return false;
	}

	int getX() {return xPosition;}
	int getY() {return yPosition;}
	int getTurn() {return turnDir;}
	int getMove() {return moveDir;}

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
	//redef copy constructor
	Board(const Board &b){
		for(int i=0; i<12; i++){
			for(int j=0; j<10; j++){
				board[i][j] = new Piece(*b.board[i][j]);
			}
		}
		filename = b.filename;
	}
	//Takes a file name as a string and creates a board object from it
	Board(string file);
	~Board(){
		/*for(int i=0; i<12; i++){
			for(int j=0; j<10; j++){
				delete board[i][j];
			}
		}*/
	}

//Accessors
	//Outputs the screen to the console
	void PrintBoard();
	//Traces the laser of the given player and returns an impact object
	Impact TraceLaser(int player);
	//returns a vector of possible plays for a given player
	vector<Play> listAllPlays(int player);
	//returns a version of the world after making a play
	Board makePlay(Play p, int pTurn){
			//apply the play to the board
		Board temp(*this);
		if(p == Play::MOVE) {
			temp.move(p);
		}
		else {
			temp.turn(p);
		}
		
		Impact kill = temp.TraceLaser(pTurn);
		temp.killer(kill);
		return temp;
	}
	//Heuristic for ranking boards relative to the passed player
	float EvaluateBoard(int player);
	//Piece* getBoard() {return board[10][12];}

	void killer(Impact kill) {
		int x = kill.getLoc().first;
		int y = kill.getLoc().second;

		if(board[x][y]->getIcon() != Wall && board[x][y]->getIcon() != Blocker && board[x][y]->getIcon() != Laser) {
			delete board[x][y];
			board[x][y] = new Piece(0, Empty);
		}
	}

	void move(Play p) {
		int x = p.getX();						//nope
		int y = p.getY();						
		int move = p.getMove();

		switch(move) {
		case Play::UP:
			delete board[x][y-1];
			board[x][y-1] = board[x][y];
			break;
		case Play::UP_RIGHT:
			delete board[x+1][y+1];
			board[x+1][y+1] = board[x][y];
			break;
		case Play::RIGHT:
			delete board[x+1][y];
			board[x+1][y] = board[x][y];
			break;
		case Play::RIGHT_DOWN:
			delete board[x+1][y-1];
			board[x+1][y-1] = board[x][y];
			break;
		case Play::DOWN:
			delete board[x][y-1];
			board[x][y-1] = board[x][y];
			break;
		case Play::DOWN_LEFT:
			delete board[x-1][y-1];
			board[x-1][y-1] = board[x][y];
			break;
		case Play::LEFT:
			delete board[x-1][y];
			board[x-1][y] = board[x][y];
			break;
		case Play::LEFT_UP:
			delete board[x-1][y+1];
			board[x-1][y+1] = board[x][y];
			break;
		}
		board[x][y] = new Piece(0, Empty);
	}
	void turn(Play p) {
		int x = p.getX();						//THESE ARE REVERSED ON PURPOSE JASH
		int y = p.getY();						//THESE ARE REVERSED ON PURPOSE RAN      //...but it doent werk
		int turn = p.getTurn();

		switch(turn) {
		case Play::CLOCKWISE:
			switch(board[x][y]->getIcon()) {
			case 217:
				board[x][y]->setIcon(192);
				break;
			case 191:
				board[x][y]->setIcon(217);
				break;
			case 218:
				board[x][y]->setIcon(191);
				break;
			case 192:
				board[x][y]->setIcon(218);
				break;
			case 47:
				board[x][y]->setIcon(92);
				break;
			case 92:
				board[x][y]->setIcon(47);
				break;
			}
			break;

		case Play::COUNTERCLOCKWISE:
			switch(board[x][y]->getIcon()) {
			case 217:
				board[x][y]->setIcon(191);
				break;
			case 191:
				board[x][y]->setIcon(218);
				break;
			case 218:
				board[x][y]->setIcon(192);
				break;
			case 192:
				board[x][y]->setIcon(217);
				break;
			case 47:
				board[x][y]->setIcon(92);
				break;
			case 92:
				board[x][y]->setIcon(47);
				break;
			}
			break;
		}
	}

private:
	//Array of pieces, going x by y
	Piece* board[12][10];
	string filename;
};

#endif