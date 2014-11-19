#include "GameMaster.h"

GameMaster::GameMaster(bool loud) { 
	p1Turn = true;			//Based upon rules, silver player moves first, and thus silver player is 0;
	noise = loud;			//How talkative it is (If we move to DirectX this won't be needed)
}
GameMaster::~GameMaster() {

}

bool GameMaster::intialize(Player& p1, Player& p2, Board& b) { //Two users, either players or AIs
	isRunning = true;
	return true;
}
void GameMaster::run() { //Run the game
	int x = 0;
	while(isRunning) {

		if(p1Turn) {
			
			p1Turn = false;
		}
		else {
			x++;
			p1Turn = true;
		}

		if(x > 5) //Just making sure it runs
			isRunning = false;
	}
}