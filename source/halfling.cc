#include <string>
#include "halfling.h"

//additional attributes: const string halflingMobID = "Halfling", const int halflingGold = 1

//default stats: Health 100, Attack 15, Defense 20, Gold: 1 pile
Halfling::Halfling(int health = 100, int attack = 15, int defense = 20) :
	Enemy(health, attack, defense, halflingMobID, halflingGold) {
	this->isMovable = true;
	this->isHostile = false;

	//this isn't essential as this might be implemented in floor later
	this->enemyLevel = 1;
}

Halfling::~Halfling() {}
