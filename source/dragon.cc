#include <string>
#include <cmath>
#include "dragon.h"

//additional attributes: const string dragonMobID = "Dragon", const int dragonGold = 1

//default stats: Health 150, Attack 20, Defense 20, Gold: 1 pile
Dragon::Dragon(int health, int attack, int defense) :
	Enemy(health, attack, defense, dragonMobID, dragonGold, 'D') {
	
	//this->type = 'D';
	
	this->isMovable = false;
	this->isHostile = false;

	//this isn't essential as this might be implemented in floor later
	this->enemyLevel = 1;
}

Dragon::~Dragon() {}
