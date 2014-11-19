

/*
By: Caelan Mayberry
Purpose: To handle the interaction between player/player, player/ai, or ai/ai
*/

class Player {};
class AI {};

class GameMaster {
public:
	GameMaster(bool loud = false);
	~GameMaster();

	bool intialize(Player& p1, Player& p2);	//Initialize the game and return if it succeeded or not.
	bool intialize(Player& p, AI& ai);
	bool intialize(AI& ai1, AI& ai2);
	void run();			//Run the game.
	
private:
	
	bool currentPlayer;
	bool noise;
	//Board world;		//Board state, will hold all information on the pieces
};