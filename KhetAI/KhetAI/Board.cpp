#include "Board.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdio.h>
using namespace std;

/* 
 Author: Josh Walton
 Course: COMP 445, AI
 Date: 18 November 2014	
 Description: defines the khetboard object, used to store a khetboard
*/

void SetColor(int ForgC)
{
     WORD wColor;
     //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

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

enum direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
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
				default:														break;

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
			if(board[i][j]->getOwner() == 0)		SetColor(7);
			else if(board[i][j]->getOwner() == 1)	SetColor(11);
			else									SetColor(10);
			cout << board[i][j]->getIcon() << " ";
			SetColor(15);
		}
		cout << endl << endl;
	}
}

//Hoo boy
Impact Board::TraceLaser(int player) {
	//boolean value for whether the beam has hit an object
	bool terminate = false;
	//value for direction laser is pointing
	int direction;
	//position coordinates for where the beam is traveling
	int xCoord;
	int yCoord;

	//Search for the laser origin so the coords can be updated
	//MODULAR
	for(int i=0; i<10; i++){
		for(int j=0; j<12; j++){
			if(board[i][j]->getIcon() == Laser && board[i][j]->getOwner() == player) {
				xCoord = i;
				yCoord = j;
			}
		}
	}

	//Determines which direction the laser starts, based on player
	//WARNING: THIS BAKES IN A LASER FACING BASED ON PLAYER, THE LASER ORIGIN SHOULD NOT CHANGE, BUT IF IT DOES, THIS BREAKS
	//Player 0 is on top
	if(player == 0) {
		direction = DOWN;
		yCoord++;
	}
	else {
		direction = UP;
		yCoord--;
	}

	while(!terminate) {
		//Switch based on direction of the beam, so the coords can be updated
		switch(direction) {
			case UP:		yCoord--;	break;
			case RIGHT:		xCoord++;	break;
			case DOWN:		yCoord++;	break;
			case LEFT:		xCoord--;	break;
			default:					break;
		}
		//Updates direction -or- returns based on where laser is looking at
		switch (board[xCoord][yCoord]->getIcon()){
			case Empty:			break;							
			case Wall:			return Impact(pair<int,int>(xCoord,yCoord),direction);
			case Laser:			return Impact(pair<int,int>(xCoord,yCoord),direction);
			case Blocker:		return Impact(pair<int,int>(xCoord,yCoord),direction);
			case King:			return Impact(pair<int,int>(xCoord,yCoord),direction); //OooOoOOooooooOOoOoOOO Ger Rekt
			case MirrorLD:		
				switch (direction){
					case UP:		direction = LEFT; break;
					case RIGHT:		direction = DOWN; break;
					case DOWN:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case LEFT:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					default:	break;
				}
			case MirrorLU:
				switch (direction){
					case UP:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case RIGHT:		direction = UP; break;
					case DOWN:		direction = LEFT; break;
					case LEFT:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					default:	break;
				}
			case MirrorRU:
				switch (direction){
					case UP:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case RIGHT:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case DOWN:		direction = RIGHT; break;
					case LEFT:		direction = UP; break;
					default:	break;
				}
			case MirrorRD:
				switch (direction){
					case UP:		direction = RIGHT; break;
					case RIGHT:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case DOWN:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case LEFT:		direction = DOWN; break;
					default:	break;
				}	
			case DMirrorFSlash: //		[/]
				switch (direction){
					case UP:		direction = RIGHT; break;
					case RIGHT:		direction = UP; break;
					case DOWN:		direction = LEFT; break;
					case LEFT:		direction = DOWN; break;
					default:	break;
				}
			case DMirrorBSlash: //		[\]
				switch (direction){
					case UP:		direction = LEFT; break;
					case RIGHT:		direction = DOWN; break;
					case DOWN:		direction = RIGHT; break;
					case LEFT:		direction = UP; break;
					default:	break;
				}
			default:	break;
		}

	}
}

float Board::EvaluateBoard(int player) {
	float value = 1;
	//Basically a running sum
	//Go through all the pieces, for each piece that is player owned, add to the running sum

	Impact imp = TraceLaser(player);
	//IMPORTANT AFTER THE TRACE LASER FUNCTION, DO THE SAME CODE FOR UPDATE BOARD TO THEN RUN THE HUERISTIC






	//Scale value based on number of pieces you have
	for(int i=0; i<10; i++){
		for(int j=0; j<12; j++){

			if(board[i][j]->getOwner() == player) {
				switch (board[i][j]->getIcon()){
					case King:			return 0;
					case MirrorLD:			value *= 4; break;
					case MirrorLU:			value *= 4; break;
					case MirrorRU:			value *= 4; break;
					case MirrorRD:			value *= 4; break;
					default:	break;
				}
			}
			//Check other guys things
			//Your pieces are valued more, so 1 for 1 trades are not encouraged
			else if(board[i][j]->getOwner() == 3 - player) {
				switch (board[i][j]->getIcon()){
					case King:				return 99999999999;	//Just like, return the best thing
					case MirrorLD:			value /= 2; break;
					case MirrorLU:			value /= 2; break;
					case MirrorRU:			value /= 2; break;
					case MirrorRD:			value /= 2; break;
					default:	break;
				}

			}
		}
	}
}
