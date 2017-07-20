#include <string>
#include "human.h"

//additional attributes: const string humanMobID = "Human", const int humanGold = 2

//default stats: Health 140, Attack 20, Defense 20, Gold: 2 piles
Human::Human(int health = 140, int attack = 20, int defense = 20) :
	Enemy(health, attack, defense, humanMobID, humanGold, 'H') {

	//this->type = 'H'; //replaces the @ initialized from the character constructor

	this->isMovable = true;
	this->isHostile = true;

	//this isn't essential as this might be implemented in floor later
	this->enemyLevel = 1; 
}

Human::~Human() {}


