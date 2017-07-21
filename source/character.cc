#include <string>
#include <vector>
#include "character.h"

using namespace std;

//attributes: curHealth, maxHealth, attack, defense

//methods below-------------------------------------
Character::Character(int myHealth, int myAttack, int myDefense, char myType) :
	Object(myType),
	curHealth{ myHealth }, maxHealth{ myHealth }, attack{ myAttack }, defense{ defense } {

}

Character::~Character() {}

//this method is responsible for this character receiving damage
//return val: true if this character is still alive after taking damage
//            false if dead after taking damage
bool Character::receiveDmg(int dmg) {
	this->setHealth(this->curHealth - dmg);
	if (this->curHealth <= 0) {
		this->setHealth(0);
		return false;
	}
	else {
		return true;
	}
}

//accessors and mutators
int Character::getHealth() {
	return this->curHealth;
}

void Character::setHealth(int newHealth) {
	if (newHealth < this->maxHealth) {
		this->curHealth = newHealth;
	}
	else {
		this->curHealth = this->maxHealth;
	}
}

int Character::getAttack() {
	return this->attack;
}

void Character::setAttack(int newAttack) {
	this->attack = newAttack;
}

int Character::getDefense() {
	return this->defense;
}

void Character::setDefense(int newDefense) {
	this->defense = newDefense;
}

string Character::getHeroType() {
	return "Character";
}

string Character::getEnemyType() {
	return "Character";
}

