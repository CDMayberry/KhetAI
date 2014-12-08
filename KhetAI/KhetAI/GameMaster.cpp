#include "GameMaster.h"

GameMaster::GameMaster(bool loud) { 
	p1Turn = true;								//Based upon rules, silver player moves first, and thus p1 is silver;
	noise = loud;								//How talkative it is (If we move to DirectX this won't be needed)
	isRunning = false;
	p1 = new Human();
	p2 = new Human();
}

GameMaster::GameMaster(string str, bool loud) {
	p1Turn = true;								//Based upon rules, silver player moves first, and thus p1 is silver;
	noise = loud;								//How talkative it is (If we move to DirectX this won't be needed)
	isRunning = false;
	world = new Board(str);
	p1 = new Human(world, true);
	p2 = new Human(world, false);
}

GameMaster::~GameMaster() {

}

bool GameMaster::intialize(Player& player1, Player& player2, Board& b) { //Sets up game and sets it ready to run.
	p1 = &player1;
	p2 = &player2;
	world = &b;			
	isRunning = true;	//Game can begin now!
	return true;
}
void GameMaster::run() { //Run the game
	int x = 0;
	while(isRunning) {

		world->PrintBoard();

		if(p1Turn) {		
			Play* temp = p1->getNextPlay();					//Gets player choice
			*world = world->makePlay(*temp, 1, true);				//Updates world with player choice
			p1Turn = false;									//Switch turns
		}
		else {
			Play* temp = p2->getNextPlay();					//Gets player choice
			*world = world->makePlay(*temp, 2, true);				//Updates world with player choice
			p1Turn = true;									//Switch turns
			x++;											//End of round, test only.
		}

		if(x > 5) //Just making sure it runs
			isRunning = false;

		//if(world.gameOver()) {
			//isRunning = false;
			//world.print()						//Or otherwise print somekind of final result
		//}
	}
}