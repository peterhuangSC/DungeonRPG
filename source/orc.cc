#include <string>
#include "orc.h"

//additional attributes: const string orcMobID = "Orc", const int orcGold = 1

//default stats: Health 180, Attack 30, Defense 25, Gold: 1 pile
Orc::Orc(int health = 180, int attack = 30, int defense = 25) :
	Enemy(health, attack, defense, orcMobID, orcGold, 'O') {

	//this->type = 'O'; //replaces the @ initialized from the character constructor

	this->isMovable = true;
	this->isHostile = true;

	//this isn't essential as this might be implemented in floor later
	this->enemyLevel = 1;
}

Orc::~Orc() {}

// this method performs the attack action
// return val: true if player(opponent) is slain by this attack, false if player is alive
bool Orc::attackPlayer(Character* player) {
	bool isPlayerSlain = false;

	//one additional attack on every hero type except for Drow as they are a type of orc too
	if (player->getHeroType().compare("Goblin") == 0) {
		int originalAttack = this->attack; //temporarily setting attack to 150%
		this->attack = floor(this->attack * goblinDamage);
		isPlayerSlain = Enemy::attackPlayer(player);
		this->attack = originalAttack;
	}
	else {
		isPlayerSlain = Enemy::attackPlayer(player);
	}
	
	return isPlayerSlain;
}



