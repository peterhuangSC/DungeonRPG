#include <iostream>
#include "ladder.h"
#include "player.h"

//char mapSymbol;

//int currentChamber;

Ladder::Ladder() : Item('\\'), currentChamber{ 1 } {}

Ladder::Ladder(int chamber) : Item('\\'), currentChamber{ chamber } {}

Ladder::~Ladder() {}

void Ladder::consume(Player* player) {
	if (player->getLevel() < 5 && player->getLevel() > 0) {
		player->levelUp();
	}
	else if (player->getLevel() == 5) {
		//you win the game
	}
	
}

