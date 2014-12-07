#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
using namespace std;

#include "Board.h"

class Player{
public:
	Player(){}
	Player(Board* b){
		gameBoard = b;
	}
	virtual Play* getNextPlay() = 0;
protected:
	Board* gameBoard;
};

class Human: public Player{
public:
	Human(){}
	Human(Board* board): Player(board){
			
	}
	Play* getNextPlay(){
		//I wrote this out completely before, but do not have time now. It just gets inputs from the player and
		//makes them into a play object which it then returns.
	}
};

class Agent: public Player{
protected:
	class AgentTree{
		friend class Agent;
		AgentTree(int c, Board* b){
			HORIZON = 5;
			Play* play = new Play(-1, -1, 0, 0); //the root gets a blank play because it is unimportant
			root = new TreeNode(*b, *play, nullptr); //this is where the root is initialized
			color = c;
		}
		class TreeNode{
			friend class AgentTree;
		public:
			TreeNode(Board world, Play play, TreeNode* p){
				thisWorld = world;
				thisPlay = play;
				parent = p;
				if(parent == nullptr){ //checks if it's the root
					ab = 1; //beta, because this is a max tier (the root)
					depth = 0;
				}else{
					ab = !p->ab;
					depth = p->depth + 1;
				}
				alphabeta = 0; //no heuristic value
			}
			float getHeuristicValue(){
				//return the world's heuristic value from thisWorld
			}
			float expand(TreeNode* p){ //the work happens here.
				//generate the entire min-max play tree all the way down to the horizon to acquire alpha valued
				//next plays to choose the next play from.
				//prune unneeded branches to reduce branching factor
				//generate a list of all possible plays and use that to make all the new worlds
				if(depth < HORIZON){
					vector<Play> possiblePlays = thisWorld.listAllPlays(color);
					TreeNode firstNode(thisWorld.makePlay(possiblePlays[0]), possiblePlays[0], this);
					alphabeta = firstNode.getHeuristicValue();
					for(int i=0; i<possiblePlays.size(); i++){ //for each play
						Board newWorld = thisWorld.makePlay(possiblePlays[i]);
						TreeNode* newNode = new TreeNode(newWorld, possiblePlays[i], this);
						children.push_back(newNode);
							//this is the pruning part. Stops expanding a node if it would never be chosen optimally
						if(ab == 1 && parent != nullptr && parent->parent != nullptr){ //if this node is < a value on the parent's level, then return it and quit expanding this branch
							for(int j=0; j < parent->parent->children.size(); j++){
								if(newNode->getHeuristicValue() < parent->parent->children[j]->alphabeta){
									return alphabeta;
								}
							}
						}else if(ab == 0 && parent != nullptr && parent->parent != nullptr){ //if this node is > a value of the paren'ts level, then return it and quit expanding this branch
							for(int j=0; j < parent->parent->children.size(); j++){
								if(newNode->getHeuristicValue() > parent->parent->children[j]->alphabeta){
									return alphabeta;
								}
							}
						}
							//this part updates alphabeta to match the best child
						float thisHeur = newNode->expand(this);
						if(ab == 0){ //if this is an alpha tier, then we're looking for the largest child
							if(thisHeur > alphabeta){
								alphabeta = thisHeur;
							}
						}else if(ab == 1){ //if this is a beta tier, then we're looking for the smallest child
							if(thisHeur < alphabeta){
								alphabeta = thisHeur;
							}
						}

					}
					return alphabeta;
				}else{
					return getHeuristicValue();
				}
			}
		private:
			TreeNode* parent; //the parent of this node
			vector<TreeNode*> children; //pointers to all possible children of this world
			Play thisPlay; //the play that lead to this world
			Board thisWorld; //the game world of this node
			bool ab; //0 == alpha, 1 == beta
			int alphabeta; //the alpha or beta value of the node
			int color;
			int depth;
		};
		TreeNode* root;
		Play* miniMax(){ //these are the three functions we can use to pick new plays
				//DFS down, generating a play and board for each world
				//do not evaluate prunable branches
			root->expand(root);
				//select the Play that generates a world with the highest value from among the immediate children of the root.
			int bestHeuristic = 0;
			int bestHeuristicIndex = 0;
			for(int i=0; i<root->children.size(); i++){
				if(root->children[i]->alphabeta > bestHeuristic){
					bestHeuristic = root->children[i]->alphabeta;
					bestHeuristicIndex = i;
				}
			}
			Play* nextPlay = new Play();
			*nextPlay = root->children[bestHeuristicIndex]->thisPlay;
			return nextPlay;
		}
		Play* negaScout(){
			
		}
		Play* monteCarlo(){
			
		}
		static int HORIZON;
		int color;
	};
	AgentTree* tree;
public:
	Agent(){}
	Agent(Board* board, bool first): Player(board){
		tree = new AgentTree(first, board);
	}
	Play* getNextPlay(){
		return tree->miniMax();
	}
private:
	int color;
};

#endif
