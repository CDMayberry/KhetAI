/*
Author: Ronald Jenkins, Caelan Mayberry, Joshua Walton
Purpose: To make a Khet game with AI!
*/

#include <iostream>
#include "GameMaster.h"

using std::cout;
using std::endl;

int main() {

	GameMaster gm;
	AI ai1;
	AI ai2;

	gm.intialize(ai1,ai2);
	gm.run();

	return 0;
}