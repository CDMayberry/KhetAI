#ifndef IMPACT_H
#define IMPACT_H
#include <utility> //std::pair

/*
By: Josh Walton
Purpose: To handle the impact of the laser on a piece, holds a pair of ints for the location and an int for the direction
This will be used to transfer information from the board to the game manager

The board has a "trace laser" funciton that returns an impact object so the game manager doesnt need to do that math
*/

class Impact {
public:
//Constructors
	//Default
	Impact() {}
	//Creates an impact object with the passed parameters
	Impact(std::pair<int,int> loc, int dir) {location = loc; direction = dir;}
//Accessors
	//Gets the location of the impact
	std::pair<int,int> getLoc() {return location;}
	//Gets the direction of the impact
	int getDir() {return direction;}

//Mutators
	//Sets the location of the laser impact
	void setLoc(std::pair<int,int> loc) {location = loc;}
	//Sets the direction of the impact
	void setDir(int dir) {direction = dir;}

private:
	//Location of the laser impact
	std::pair<int,int> location;
	//Direction of the laser impact, follows convention
	int direction;
};

#endif