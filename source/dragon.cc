#include <string>
#include <cmath>
#include "dragon.h"

// This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) 
//additional attributes: const string dragonMobID = "Dragon", const int dragonGold = 1

//default stats: Health 150, Attack 20, Defense 20, Gold: 1 pile
Dragon::Dragon(int health, int attack, int defense) :
	Enemy(health, attack, defense, "Dragon", 'D') {
	
	this->isMovable = false;
	this->isHostile = true;

	this->enemyLevel = 1;
}

Dragon::~Dragon() {}

bool Dragon::canMove() {
	return false;
}

bool Dragon::receiveDmg(int dmg) {
	//dragon is now hostile
	//but more so this has to be set in the map b/c if you move within
	//+/- 1 vertical +/- 1 horizontal of dragon and/or its hoard hostile is set to true
	//and this can only be done in map or game due to the coordinates known there
	if (this->isHostile == false) this->isHostile = true;

	this->setHealth(this->curHealth - dmg);
	if (this->curHealth <= 0) {
		this->setHealth(0);
		return false;
	}
	else {
		return true;
	}
}
