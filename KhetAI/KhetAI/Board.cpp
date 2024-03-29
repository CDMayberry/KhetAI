#include "Board.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <queue>
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

enum direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

Board::Board() {
	for(int i=0; i<12; i++){
		for(int j=0; j<10; j++){
			board[i][j] = new Piece();
		}
	}
};

Board::Board(string file) {
	fstream fin;
	char temp;
	fin.open(file + ".txt");

	for(int j=0; j<10; j++){
		for(int i=0; i<12; i++){
			fin >> temp;
			switch(temp) {
				case '_': board[i][j] = new Piece(0,Empty);				break;
				case 'W': board[i][j] = new Piece(0,Wall);				break;
				case 'L': board[i][j] = new Piece(0,Laser);				break;
				case 'B': board[i][j] = new Piece(0,Blocker);			break;
				case 'K': board[i][j] = new Piece(0,King);				break;
				case '1': board[i][j] = new Piece(0,MirrorLD);			break;
				case '2': board[i][j] = new Piece(0,MirrorLU);			break;
				case '3': board[i][j] = new Piece(0,MirrorRU);			break;
				case '4': board[i][j] = new Piece(0,MirrorRD);			break;
				case '5': board[i][j] = new Piece(0,DMirrorFSlash);		break;
				case '6': board[i][j] = new Piece(0,DMirrorBSlash);		break;
				default:												break;

			}
		}
		//fin.get();
	}

	for(int j=0; j<10; j++){
		for(int i=0; i<12; i++){
			fin >> temp;
			board[i][j]->setOwner((int)temp - 48);
		}
		//fin.get();
	}
}

//Outputs the screen to the console
void Board::PrintBoard() {
	for(int j=0; j<10; j++){
		for(int i=0; i<12; i++){
			if(board[i][j]->getOwner() == 0)		
				SetColor(7);
			else if(board[i][j]->getOwner() == 1)	
				SetColor(11);
			else									
				SetColor(10);
			cout << (char)board[i][j]->getIcon() << " ";
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
	for(int i=0; i<12; i++){
		for(int j=0; j<10; j++){
			if(board[i][j]->getIcon() == Laser && board[i][j]->getOwner() == player) {
				xCoord = i;
				yCoord = j;
				break;
			}
		}
	}

	//Determines which direction the laser starts, based on player
	//WARNING: THIS BAKES IN A LASER FACING BASED ON PLAYER, THE LASER ORIGIN SHOULD NOT CHANGE, BUT IF IT DOES, THIS BREAKS
	//Player 1 is on top
	if(player == 1) {
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
				break;
			case MirrorLU:
				switch (direction){
					case UP:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case RIGHT:		direction = UP; break;
					case DOWN:		direction = LEFT; break;
					case LEFT:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					default:	break;
				}
				break;
			case MirrorRU:
				switch (direction){
					case UP:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case RIGHT:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case DOWN:		direction = RIGHT; break;
					case LEFT:		direction = UP; break;
					default:	break;
				}
				break;
			case MirrorRD:
				switch (direction){
					case UP:		direction = RIGHT; break;
					case RIGHT:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case DOWN:		return Impact(pair<int,int>(xCoord,yCoord),direction);
					case LEFT:		direction = DOWN; break;
					default:	break;
				}	
				break;
			case DMirrorFSlash: //		[/]
				switch (direction){
					case UP:		direction = RIGHT; break;
					case RIGHT:		direction = UP; break;
					case DOWN:		direction = LEFT; break;
					case LEFT:		direction = DOWN; break;
					default:	break;
				}
				break;
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

vector<Play> Board::listAllPlays(int player){ //mmmmmm. nothing like quad-nested for loops. :)
	player++; //to make it match with the way it works in board
		//find all plays that can be made by a player
	vector<Play> possiblePlays;
	for(int i=0; i<10; i++){ //x
		for(int j=0; j<12; j++){ //y
				// if it's the correct player
			if(board[i][j]->getOwner() == player && board[i][j]->getIcon() != Laser){
					//make a play for both rotation options
				if(board[i][j]->getIcon() != King && board[i][j]->getIcon() != Blocker){
					if(board[i][j]->getIcon() != DMirrorFSlash && board[i][j]->getIcon() != DMirrorBSlash){
						possiblePlays.push_back(Play(i, j, 1, Play::CLOCKWISE));
					}
					possiblePlays.push_back(Play(i, j, 1, Play::COUNTERCLOCKWISE));
				}
					//make a play for all available movement options
				for(int k=-1; k<=1; k++){
					for(int l=-1; l<=1; l++){
						if(k != 0 && l != 0 && //if the desired move location isn't where the piece already is
							i+k>0 && i+k<10 && //and it's within bounds
							j+l>0 && j+l<12){
							if(board[i+k][j+l]->getIcon() == Empty){ //and it's empty
									//these are all the different directions
								if(k == 0 && l == 1){ //up
									possiblePlays.push_back(Play(i, j, 0, Play::UP));
								}
								if(k == 1 && l == 1){ //up-right
									possiblePlays.push_back(Play(i, j, 0, Play::UP_RIGHT));
								}
								if(k == 1 && l == 0){ //right
									possiblePlays.push_back(Play(i, j, 0, Play::RIGHT));
								}
								if(k == 1 && l == -1){ //right-down
									possiblePlays.push_back(Play(i, j, 0, Play::RIGHT_DOWN));
								}
								if(k == 0 && l == -1){ //down
									possiblePlays.push_back(Play(i, j, 0, Play::DOWN));
								}
								if(k == -1 && l == -1){ //down-left
									possiblePlays.push_back(Play(i, j, 0, Play::DOWN_LEFT));
								}
								if(k == -1 && l == 0){ //left
									possiblePlays.push_back(Play(i, j, 0, Play::LEFT));
								}
								if(k == -1 && l == 1){ //left-up
									possiblePlays.push_back(Play(i, j, 0, Play::LEFT_UP));
								}
							}
						}
					}
				}
			}
		}
	} //like a waterfall ^
	return possiblePlays;
}

float Board::EvaluateBoard(int player) {
	float value = 1;
	int xKing;
	int yKing;
	int xLaser;
	int yLaser;
	int direction;

	//Basically a running sum
	//Go through all the pieces, for each piece that is player owned, add to the running sum

	struct xyNode{
		int x;
		int y;
		int direction;		
		float g;
		float h;

		xyNode(int xt,int yt,int dirt,float gt,float ht) {
			x = xt;
			y = yt;
			direction = dirt;
			g = gt;
			h = ht;
		}

		bool operator==(xyNode n) {
			if(n.x == x	&& n.y == y	&& n.direction == direction	&& n.g == g	&& n.h == h)
				return true;
			else
				return false;
		}

	};

	//Find your Laser
	for(int i=0; i<12; i++){
		for(int j=0; j<10; j++){
			if(board[i][j]->getIcon() == Laser && board[i][j]->getOwner() == player) {
				xLaser = i;
				yLaser = j;
				break;
			}
		}
	}
	//Find their King
	for(int i=0; i<12; i++){
		for(int j=0; j<10; j++){
			if(board[i][j]->getIcon() == King && board[i][j]->getOwner() != player) {
				xKing = i;
				yKing = j;
				break;
			}
		}
	}
	
	//get which direction to start
	if(player == 1) {
		direction = DOWN;
	}
	else {
		direction = UP;
	}

	auto mannDistance = [=](int xSta, int ySta, int xTar, int yTar) -> int {
		int dis = yTar - ySta + xTar - xSta;
		if(dis < 0)
			return -dis;
		else
			return dis;
	};

	auto mirrorDist = [=](pair<int,int> p) -> int {
		/*vector<pair<int,int>> mirrors;
		for(unsigned int i = 0; i < 12; i++) {
			for(unsigned int j = 0; j < 10; j++) {
				if((board[i][j]->getIcon() == MirrorLD || 
					board[i][j]->getIcon() == MirrorLU || 
					board[i][j]->getIcon() == MirrorRD ||
					board[i][j]->getIcon() == MirrorRU ) &&
					board[i][j]->getOwner() == player) 
					mirrors.push_back(pair<int,int>(i,j));
			}
		}
		int closestIndex = 0;
		int smallestDist = mannDistance(mirrors[0].first,mirrors[0].second,p.first,p.second);
		for(unsigned int i=0; i < mirrors.size(); i++) {
			if(mannDistance(mirrors[i].first,mirrors[i].second,p.first,p.second < smallestDist)) {
				smallestDist = mannDistance(mirrors[i].first,mirrors[i].second,p.first,p.second); 
				closestIndex = i;
			}
		}
		return mannDistance(mirrors[closestIndex].first,mirrors[closestIndex].second,p.first,p.second);*/
		return 10;
	};
	
	auto aStar = [=](int xStart, int yStart, int xTarget, int yTarget) -> float {
		vector<xyNode> evaluated;
		vector<xyNode> frontier;
		frontier.push_back(xyNode(xStart,yStart,direction,0,mannDistance(xStart,yStart,xKing,yKing)));
		
		float runningCost = 0;
		int x = xStart;
		int y = yStart;
		int cost = 0;
		int indexMin = 0;
		

		while(frontier.size() > 0 && frontier.size() < 10) {

			if(frontier.size() > 1) {
				//Search the frontier for the minimum cost
				for(unsigned int i = 0; i <frontier.size(); i++) {
					//Assign it the first one
					float temp = frontier.front().h;
					if(frontier[i].h < temp)
						temp = frontier[i].h;
						indexMin = i;
				}
			}
			else
				indexMin = 0;

			//After finding the node to evaulate, take it off the frontier and expand that nonsense
			xyNode myNode(frontier[indexMin]);
			frontier.erase(frontier.begin() + indexMin);
			evaluated.push_back(myNode);

			int turningG = myNode.g + 1 + mirrorDist(pair<int,int>(myNode.x,myNode.y));

			//Push on new neighbors
			switch(myNode.direction) {
				case UP:
					//push up,right,left
					if(y>0) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x,y-1,UP,myNode.g + 1,myNode.g + 1 + mannDistance(x,y-1,xKing,yKing))) == evaluated.end() ) 
							frontier.push_back(xyNode(x,y-1,UP,myNode.g + 1,myNode.g + 1 + mannDistance(x,y-1,xKing,yKing)));
					}
					if(x<12) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x+1,y,RIGHT,turningG,turningG + mannDistance(x+1,y,xKing,yKing))) ==	evaluated.end() ) 
							frontier.push_back(xyNode(x+1,y,RIGHT,turningG,turningG + mannDistance(x+1,y,xKing,yKing)));
					}
					if(x>0) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x-1,y,LEFT,turningG,turningG + mannDistance(x-1,y,xKing,yKing))) == evaluated.end() ) 
							frontier.push_back(xyNode(x-1,y,LEFT,turningG,turningG + mannDistance(x-1,y,xKing,yKing)));
					}
					break;
				case RIGHT:
					//push right,down,up
					if(y<10) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x,y+1,DOWN,turningG,turningG + mannDistance(x,y+1,xKing,yKing))) == evaluated.end() ) 
						frontier.push_back(xyNode(x,y+1,DOWN,turningG,turningG + mannDistance(x,y+1,xKing,yKing)));
					}
					if(y>0) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x,y-1,UP,turningG,turningG + mannDistance(x,y-1,xKing,yKing))) == evaluated.end() ) 
						frontier.push_back(xyNode(x,y-1,UP,turningG,turningG + mannDistance(x,y-1,xKing,yKing)));
					}
					if(x<12) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x+1,y,RIGHT,myNode.g + 1,myNode.g + 1 + mannDistance(x+1,y,xKing,yKing))) == evaluated.end() ) 
						frontier.push_back(xyNode(x+1,y,RIGHT,myNode.g + 1,myNode.g + 1 + mannDistance(x+1,y,xKing,yKing)));
					}
					break;
				case DOWN:
					//push down,left,right
					if(y<10) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x,y+1,DOWN,myNode.g + 1,myNode.g + 1 + mannDistance(x,y+1,xKing,yKing))) == evaluated.end() ) 
						frontier.push_back(xyNode(x,y+1,DOWN,myNode.g + 1,myNode.g + 1 + mannDistance(x,y+1,xKing,yKing)));
					}
					if(x<12) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x+1,y,RIGHT,turningG,turningG + mannDistance(x+1,y,xKing,yKing))) == evaluated.end() ) 
						frontier.push_back(xyNode(x+1,y,RIGHT,turningG,turningG + mannDistance(x+1,y,xKing,yKing)));
					}
					if(x>0) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x-1,y,LEFT,turningG,turningG + mannDistance(x-1,y,xKing,yKing))) == evaluated.end() ) 
						frontier.push_back(xyNode(x-1,y,LEFT,turningG,turningG + mannDistance(x-1,y,xKing,yKing)));
					}
					break;
				case LEFT:
					//push left,up,down
					if(y<10) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x,y+1,DOWN,turningG,turningG + mannDistance(x,y+1,xKing,yKing)))	==	 evaluated.end() ) 
						frontier.push_back(xyNode(x,y+1,DOWN,turningG,turningG + mannDistance(x,y+1,xKing,yKing)));
					}
					if(y>0) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x,y-1,UP,turningG,turningG + mannDistance(x,y-1,xKing,yKing))) == evaluated.end() ) 
						frontier.push_back(xyNode(x,y-1,UP,turningG,turningG + mannDistance(x,y-1,xKing,yKing)));
					}
					if(x>0) {
						if(find(evaluated.begin(),evaluated.end(),xyNode(x-1,y,LEFT,myNode.g + 1,myNode.g + 1 + mannDistance(x-1,y,xKing,yKing))) == evaluated.end() ) 
						frontier.push_back(xyNode(x-1,y,LEFT,myNode.g + 1,myNode.g + 1 + mannDistance(x-1,y,xKing,yKing)));
					}
					break;
				default: break;
			}

			for(unsigned int i = 0; i < frontier.size(); i++) {
				if(mannDistance(frontier[i].x,frontier[i].y,xKing,yKing) == 0)
					return frontier[i].g;
			}

		}

	};

	vector<pair<int,int>> targets;

	for(unsigned int i = 0; i < 12; i++) {
		for(unsigned int j = 0; j < 10; j++) {
			if(board[i][j]->getOwner() != player) {
				if(board[i][j]->getIcon() == King || board[i][j]->getIcon() == MirrorLD || board[i][j]->getIcon() == MirrorLU || board[i][j]->getIcon() == MirrorRD || board[i][j]->getIcon() ==MirrorRU) {
					targets.push_back(pair<int,int>(i,j));
				}
			}
		}
	}
	
	for( unsigned int i = 0; i < targets.size(); i++) {
		value += aStar(xLaser,yLaser,targets[i].first,targets[i].second);
	}

	//NOTE THIS DOESNT CHANGE THE BOARD



	bool yourKingDead = true;
	bool theirKingDead = true;

	//Scale value based on number of pieces you have
	for(int i=0; i<10; i++){
		for(int j=0; j<12; j++){

			if(board[i][j]->getOwner() == player) {
				switch (board[i][j]->getIcon()){
					case King:				yourKingDead = false; break;
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
					case King:				theirKingDead = false; break;
					case MirrorLD:			value /= 2; break;
					case MirrorLU:			value /= 2; break;
					case MirrorRU:			value /= 2; break;
					case MirrorRD:			value /= 2; break;
					default:	break;
				}

			}
		}
	}
	if(yourKingDead)
		return 0;
	if(theirKingDead)
		return 999999999;
	return value;

}
