#include <string>
#include <cmath>
#include "human.h"

//additional attributes: const string humanMobID = "Human", const int humanGold = 2

//default stats: Health 140, Attack 20, Defense 20, Gold: 2 piles
Human::Human(int health, int attack, int defense) :
	Enemy(health, attack, defense, "Human", 'H') {

	this->isMovable = true;
	this->isHostile = true;

	this->enemyLevel = 1; 
}

Human::~Human() {}
