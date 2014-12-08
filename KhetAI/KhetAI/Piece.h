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
	Piece(int own, int ico) {owner=own; icon=ico;}
//Accessors
	//Gets the icon of the piece
	int getIcon() {return icon;}
	//Gets the owner of the piece
	int getOwner() {return owner;}

//Mutators
	//Sets the icon of the piece
	void setIcon(int ico) {icon=ico;}
	//Sets the owner of the piece
	void setOwner(int own) {owner=own;}

	bool operator==(int icon) {
		if(icon == getIcon())
			return true;
		return false;
	}

private:
	//Owner of the piece, 0 for no one, 1 or 2 corresponding to player
	int owner;
	//Icon indicating type of piece
	int icon;
};

#endif