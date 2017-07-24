#include <string>
#include <vector>
#include "character.h"

using namespace std;

//attributes: curHealth, maxHealth, attack, defense, shared_ptr<potion> potionBuffs

//methods below-------------------------------------
Character::Character(int myHealth, int myAttack, int myDefense, char myType) :
	Object(myType),	curHealth{ myHealth }, maxHealth{ myHealth }, 
	attack{ myAttack }, defense{ myDefense }, curAction{ "default" } {

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
	return max(this->curHealth, 0);
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
	if (this->potionBuffs) {
		int addedAttack = this->potionBuffs->potionBuffers()[0];
		return max(this->attack + addedAttack, 0);
	}
	else {
		return max(this->attack, 0);
	}
}

void Character::setAttack(int newAttack) {
	this->attack = newAttack;
}

int Character::getDefense() {
	if (this->potionBuffs) {
		int addedDefense = this->potionBuffs->potionBuffers()[1];
		return max(this->defense + addedDefense, 0);
	}
	else {
		return max(this->defense, 0);
	}
}

void Character::setDefense(int newDefense) {
	this->defense = newDefense;
}

shared_ptr<Object> Character::getPotionBuffs() {
	return this->potionBuffs;
}

void Character::consumePotion(shared_ptr<Object> myPotion) {
	//case 1: consume health related potions
	myPotion->setKnown();
	if (myPotion->getPotionName().compare("Restore Health") == 0 ||
		myPotion->getPotionName().compare("Poison Health") == 0) {
		this->setHealth(this->getHealth() + myPotion->getHealthEffect());
		curAction += " PC consumed a: " + myPotion->getPotionName();
		curAction += ".";
		return;
	}

	//blue bar for boosted/weakened attack/defense
	if (!potionBuffs) {
		potionBuffs = myPotion; 
	}
	else {
		myPotion->setNextPotion(potionBuffs);
		potionBuffs = myPotion;
	}
	curAction += " PC consumed a: " + myPotion->getPotionName();
	curAction += ".";
}

string Character::getAction() {
	return this->curAction;
}

void Character::setAction(string newAction) {
	this->curAction = newAction;
}

void Character::appendAction(string appAction) {
	this->curAction += appAction;
}

