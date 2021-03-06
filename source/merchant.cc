#include <string>
#include <cmath>
#include "merchant.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */
//additional attributes: const string merchantMobID = "Merchant", const int merchantGold = 1

bool Merchant::mercHostile = false;

//default stats: Health 30, Attack 70, Defense 5, <Gold: 1 pile?? check this>
Merchant::Merchant(int health, int attack, int defense) :
	Enemy(health, attack, defense, "Merchant", 'M') {

	this->isMovable = true;
	this->isHostile = false;

	this->enemyLevel = 1;
}

Merchant::~Merchant() {}

bool Merchant::canMove() {
	if (mercHostile) return true;
	else return false;
}

bool Merchant::receiveDmg(int dmg) {
	mercHostile = true;
	//merchant attributes after it is attacked the first time
	//but the map/game class has to be also changed so all merchants are set 
	//to hostile after the first one is attacked
	if (this->isHostile == false) this->isHostile = true;
	if (this->isMovable == false) this->isMovable = true;

	this->setHealth(this->curHealth - dmg);
	if (this->curHealth <= 0) {
		this->setHealth(0);
		return false;
	}
	else {
		return true;
	}
}

//severTies() already exists from the superclass

void Merchant::resetStatic() {
	mercHostile = false;
}

//note: isHostile will only affect one instance of merchant
// we need to use the static variable here
bool Merchant::getHostility() {
	return mercHostile;
}
