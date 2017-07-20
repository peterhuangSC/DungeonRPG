#include <string>
#include "merchant.h"

//additional attributes: const string merchantMobID = "Merchant", const int merchantGold = 1

//default stats: Health 30, Attack 70, Defense 5, <Gold: 1 pile?? check this>
Merchant::Merchant(int health = 30, int attack = 70, int defense = 5) :
	Enemy(health, attack, defense, merchantMobID, merchantGold, 'M') {

	//this->type = 'M'; //replaces the @ initialized from the character constructor

	this->isMovable = true;
	this->isHostile = false;

	//this isn't essential as this might be implemented in floor later
	this->enemyLevel = 1;
}

Merchant::~Merchant() {}

//severTies() already exists from the superclass

