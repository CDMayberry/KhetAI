#include "GameMaster.h"

GameMaster::GameMaster(bool loud) { 
	p1Turn = true;								//Based upon rules, silver player moves first, and thus p1 is silver;
	noise = loud;								//How talkative it is (If we move to DirectX this won't be needed)
	isRunning = false;
}
GameMaster::~GameMaster() {

}

bool GameMaster::intialize(Player& p1, Player& p2, Board& b) { //Sets up game and sets it ready to run.
	world = &b;			//I wonder...
	isRunning = true;	//
	return true;
}
void GameMaster::run() { //Run the game
	int x = 0;
	while(isRunning) {

		if(p1Turn) {
			//event* ev = p1.takeTurn(world)	//Gets player choice
			//world.update(ev);					//Updates world with player choice

			p1Turn = false;						//Switch turns
		}
		else {
			//event* ev = p2.takeTurn(world)	//Gets player choice
			//world.update(ev);					//Updatse world with player choice
			x++;								//End of round, test only.
			p1Turn = true;						//Switch turns
		}

		if(x > 5) //Just making sure it runs
			isRunning = false;

		//if(world.gameOver()) {
			//isRunning = false;
			//world.print()						//Or otherwise print somekind of final result
		//}
	}
}