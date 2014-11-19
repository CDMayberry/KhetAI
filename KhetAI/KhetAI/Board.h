#ifndef KHETBOARD_H
#define KHETBOARD_H

#include <iostream>
#include <string>
#include <fstream>
#include "Piece.h"
using namespace std;

/* 
 Author: Josh Walton
 Course: COMP 445, AI
 Date: 18 November 2014	
 Description: defines the khetboard object, used to store a khetboard
*/

enum Move {
	RotateLeft,
	RotateRight,
	MoveLeft,
	MoveUp,
	MoveRight,
	MoveDown,
};


class Board{
public:
//Constructors
	Board();
	Board(string file);

//Accessors
//Mutators
	//Reads the data from a file 
	void readBoard(string f){
		filename = f;
		fin.open(filename);

		char tempChar;
		for(int i=0; i<12; i++){
			for(int j=0; j<10; j++){
				fin >> tempChar;
				board[i][j].setIcon(tempChar);
			}
		}
		int tempInt;
		for(int i=0; i<12; i++){
			for(int j=0; j<10; j++){
				fin >> tempInt;
				board[i][j].setOwner(tempInt);
			}
		}
	}
	/*
	//Creates a new file with the same name as the input appended with _output
	void openOut(){
		string filenameout;
		for(unsigned int i=0; i<filename.size()-4; i++){
			filenameout += filename[i];
		}
		fout.open(filenameout + "_output.txt");
	}
	//Streams sudokuboard to the fout filestream
	void write(SudokuBoard t){
		for(int i=0; i<9; i++){
			for(int j=0; j<9; j++){
				if(t.getValueID(i, j) != -1){
					fout << t.getValueID(i, j) << " ";
				}else{
					fout << "_ ";
				}
			}
			fout << endl;
		}
	}
	*/
private:
	//Array of pieces, going x by y
	Piece board[12][10];
	string filename;
	ifstream fin;
	ofstream fout;
};

#endif