//I want to note that more of this WAS written, but due to a 'getting used to GitHub' error, much of
//it was tragically erased. MAR. :(
/*
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
using namespace std;

#include "Board.h"

class Player{
public:
	Player(Board* b): gameBoard(b) {}
protected:
	enum play_type{MOVE, TURN};
	enum move_directions{UP, UP_RIGHT, RIGHT, RIGHT_DOWN, DOWN, DOWN_LEFT, LEFT, LEFT_UP};
	enum turn_directions{CLOCKWISE, COUNTERCLOCKWISE};
	class Play{
	public:
		Play(int x, int y, int pType, int moveORturnDirection){
			xPosition = x;
			yPosition = y;
			playType = pType;
			if(pType == MOVE){
				moveDir = moveORturnDirection;
			}else if(pType == TURN){
				turnDir = moveORturnDirection;
			}
		}
	private:
		int playType; //0 for move, 1 for turn
		int moveDir;
		int turnDir;
		int xPosition, yPosition;
	};
	virtual Play* getNextPlay() = 0;
	Board* gameBoard;
};

class Human: public Player{
	Play* getNextPlay(){
		//I wrote this out completely before, but do not have time now. It just gets inputs from the player and
		//makes them into a play object which it then returns.
	}
};

class Agent: public Player{
protected:
	class AgentTree{
		friend class Agent;
		AgentTree(bool first, Board* b){
			HORIZON = 10;
			Play* play = new Play(-1, -1, 0, 0);
			root = new TreeNode(*b, *play);
		}
		class TreeNode{
			friend class AgentTree;
		public:
			TreeNode(Board world, Play play){
				
			}
			void build(){
				//creates new children up to the horizon
			}
		private:
			TreeNode* parent;
			vector<TreeNode*> children;
			Play thisPlay;
			Board thisWorld;
		};
		TreeNode* root;
		Play* miniMax(){ //these are the three functions we can use to pick new plays

		}
		Play* negaScout(){
			
		}
		Play* monteCarlo(){
			
		}
		int HORIZON;
	};
	AgentTree* tree;
public:
	Agent(bool first, Board* b): Player(b) {
		tree = new AgentTree(first b);
	}
	Play* getNextPlay(){
		return tree.miniMax();
	}
};

#endif
*/