#include <string>
#include "elf.h"

//additional attributes: const string elfMobID = "Elf", const int elfGold = 1

//default stats: Health 140, Attack 30, Defense 10, Gold: 1 pile
Elf::Elf(int health = 140, int attack = 30, int defense = 10) :
	Enemy(health, attack, defense, elfMobID, elfGold, 'E') {

	//this->type = 'E'; //replaces the @ initialized from the character constructor

	this->isMovable = true;
	this->isHostile = true;

	//this isn't essential as this might be implemented in floor later
	this->enemyLevel = 1;
}

Elf::~Elf() {}

// this method performs the attack action
// return val: true if player(opponent) is slain by this attack, false if player is alive
bool Elf::attackPlayer(Character* player) {
	bool isPlayerSlain = false;
		
	//one additional attack on every hero type except for Drow as they are a type of elf too
	if (player->getHeroType().compare("Drow") != 0) {
		isPlayerSlain = Enemy::attackPlayer(player);
	}
	
	//if the player is not dead the elf gets to attack again
	if (isPlayerSlain == false) {
		isPlayerSlain = Enemy::attackPlayer(player);
	}

	return isPlayerSlain;
}



