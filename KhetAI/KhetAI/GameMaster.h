/*
By: Caelan Mayberry
Purpose: To handle the interaction between player/player, player/ai, or ai/ai
*/

#include "Player.h"
#include "Board.h"

class GameMaster {
public:
	GameMaster(bool loud = false);
	~GameMaster();

	bool intialize(Player& p1, Player& p2, Board& b);	//Initialize the game and return if it succeeded or not.
	void run();			//Run the game.
	void draw();

private:
	bool isRunning;
	bool p1Turn;
	bool noise;
	Board* world;		//Board state, will hold all information on the pieces
	Player* p1;
	Player* p2;
};