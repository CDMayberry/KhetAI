#ifndef PIECE_H
#define PIECE_H

/*
By: Josh Walton
Purpose: To handle each individual piece on the khet board
*/

class Piece {
public:
//Constructors
	Piece() {}
	Piece(int own, char ico) {owner=own; icon=ico;}
//Accessors
	//Gets the icon of the piece
	char getIcon() {return icon;}
	//Gets the owner of the piece
	int getOwner() {return owner;}

//Mutators
	//Sets the icon of the piece
	void setIcon(char ico) {icon=ico;}
	//Sets the owner of the piece
	void setOwner(int own) {owner=own;}

private:
	//Owner of the piece, 0 for no one, 1 or 2 corresponding to player
	int owner;
	//Icon indicating type of piece
	char icon;
};

#endif