#include <string>
#include <cmath>
#include "orc.h"

using namespace std;

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */
//additional attributes: const string orcMobID = "Orc", const int orcGold = 1

//default stats: Health 180, Attack 30, Defense 25, Gold: 1 pile
Orc::Orc(int health, int attack, int defense) :
	Enemy(health, attack, defense, "Orc", 'O'),
	goblinDamage{ 1.5 } {

	this->isMovable = true;
	this->isHostile = true;

	this->enemyLevel = 1;
}

Orc::~Orc() {}

// this method performs the attack action
// return val: true if player(opponent) is slain by this attack, false if player is alive
bool Orc::attackPlayer(shared_ptr<Object> player) {
	bool isPlayerSlain = false;

	//150% damage attack on Goblin hero types
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

