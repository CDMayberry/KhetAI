/*
Author: Ronald Jenkins, Caelan Mayberry, Joshua Walton
Purpose: To make a Khet game with AI!
*/

/*
DIRECTX COMPATIBILITY:
Make sure board knows where all of the pieces are and each piece knows its X and Y location on the board,
Even if they aren't used.

All Pieces will become a derived class of Entity, a class from games 1, if we do convert,
and that should be able to handle drawing and screen location information.

Board will need to handle information changes and check for 'collisions' with the laser.
*/

#include <iostream>
#include "GameMaster.h"

using std::cout;
using std::endl;

int main() {

	GameMaster gm(true);
	Board board("1");
	Human p1(&board, true);
	Human p2(&board, false);
	gm.intialize(p1, p2, board);
	gm.run();



	//Board test("1");
	//test.PrintBoard();

	system("pause");
	return 0;
}