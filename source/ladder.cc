#include <iostream>
#include "ladder.h"
#include "player.h"

using namespace std;

//char mapSymbol;
//int currentChamber;
/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

Ladder::Ladder() : Item('\\'), currentChamber{ 1 } {}

Ladder::Ladder(int chamber) : Item('\\'), currentChamber{ chamber } {}

Ladder::~Ladder() {}

//thinking of swapping this function to be put in player, under construction
// dont use this function
void Ladder::consumeLadder(shared_ptr<Object> player) {
	if (player->getLevel() < 5 && player->getLevel() > 0) {
		player->levelUp();
		//remove potions
	}
	else if (player->getLevel() == 5) {
		//you win the game
	}
	
}

