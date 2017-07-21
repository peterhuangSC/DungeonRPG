#include <string>
#include <cmath>
#include "halfling.h"

//additional attributes: const string halflingMobID = "Halfling", const int halflingGold = 1

//default stats: Health 100, Attack 15, Defense 20, Gold: 1 pile
Halfling::Halfling(int health, int attack, int defense) :
	Enemy(health, attack, defense, halflingMobID, halflingGold, 'L') {

	//this->type = 'L'; //replaces the @ initialized from the character constructor

	this->isMovable = true;
	this->isHostile = false;

	//this isn't essential as this might be implemented in floor later
	this->enemyLevel = 1;
}

Halfling::~Halfling() {}
