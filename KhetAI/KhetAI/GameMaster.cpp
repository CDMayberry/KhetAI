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

bool GameMaster::run() { //Run the game
	
	world->PrintBoard();

	while(isRunning) {

		//system("cls");
		
		Play* temp = p1->getNextPlay(world);					//Gets player choice
		*world = world->makePlay(*temp, 1);				//Updates world with player choice
		world->PrintBoard();
		cout << "\nPlayer one took a turn.\n\n";
		
		////checks if the game is finished
		//if(world->isFinished()){
		//	cout << "Player one won! Congratulation, the story is happy end." << endl;
		//	return 0;
		//}

		Play* temp2 = p2->getNextPlay(world);					//Gets player choice
		*world = world->makePlay(*temp2, 2);				//Updates world with player choice
		world->PrintBoard();
		cout << "\nPlayer two took a turn.\n\n" << endl;
		
		//system("pause");

		////checks if the game is finished
		//if(world->isFinished()){
		//	cout << "Player two won! Congratulation, the story is happy end." << endl;
		//	return 1;
		//}

		
	}
	return true;
}