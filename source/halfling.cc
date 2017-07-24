#include <string>
#include <cmath>
#include "halfling.h"

//additional attributes: const string halflingMobID = "Halfling", const int halflingGold = 1

//default stats: Health 100, Attack 15, Defense 20, Gold: 1 pile
Halfling::Halfling(int health, int attack, int defense) :
	Enemy(health, attack, defense, "Halfling", 'L'),
	dodgeRate{ 0.5 } {

	this->isMovable = true;
	this->isHostile = true;

	this->enemyLevel = 1;
}

Halfling::~Halfling() {}
