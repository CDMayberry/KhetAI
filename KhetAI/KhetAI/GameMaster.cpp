#include "GameMaster.h"

GameMaster::GameMaster(bool loud) { 
	currentPlayer = 0; //Based upon rules, silver player moves, and thus silver player is 0;
	noise = loud;			//How talkative it is (If we move to DirectX this won't be needed)
}
GameMaster::~GameMaster() {

}

bool GameMaster::intialize(Player& p1, Player& p2) { //Player vs Player

	return true;
}
bool GameMaster::intialize(Player& p, AI& ai) { //Player vs AI

	return true;
}
bool GameMaster::intialize(AI& ai1, AI& ai2) { //AI vs AI

	return true;
}
void GameMaster::run() { //Run the game

}