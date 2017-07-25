#include <string>
#include "object.h"

/* This project was coded & developed by:
Peter Huang (zh3huang) and Shane Mazur (smazur) */

Object::Object(char typeSymbol) : type{ typeSymbol }, 
	potionBuffs{ nullptr },	hadTurn{ false } {
	//no implementation currently
}

Object::~Object() {}

void Object::setType(char newType) {
	this->type = newType;
}

char Object::getType() {
	return this->type;
}

std::string Object::getHeroType() {
	return "Object";
}
std::string Object::getEnemyType() {
	return "Object";
};

int Object::getHealth() { return -1; }
void Object::setHealth(int newHealth) {}

int Object::getAttack() { return -1; }

int Object::getDefense() { return -1; }

int Object::getValue() { return 0; }
int Object::getQuantity() { return 0; }

int Object::getLevel() { return 1; }
void Object::levelUp() {} //overriden in player - increase level and delete buffer potions
int Object::getGold() { return -1; }
void Object::addGold(int myGold) {}
bool Object::addGoldItem(std::shared_ptr<Object> myGold) { return false; }

void Object::notify(std::shared_ptr<Object> who) {
	// to be implemented
}

//bool Object::consumeGold(std::shared_ptr<Object> myObj) { return false; }

void Object::consumeLadder(std::shared_ptr<Object> player) {}

bool Object::isGuarded() { return false; }

void Object::setGuarded() {}
void Object::setUnguarded() {}

std::string Object::getAction() {
	return "n/a";
}
void Object::setAction(std::string newAction) {}
void Object::appendAction(std::string appAction) {}

void Object::severTies() {}

bool Object::canMove() { return false; }

void Object::consumePotion(std::shared_ptr<Object> myPotion) {}

std::string Object::getPotionName() { return "n/a"; }

int Object::getHealthEffect() { return 0; }

int Object::getAttackEffect() { return 0; }
int Object::getDefenseEffect() { return 0; }

void Object::setAttackEffect(int value) {}
void Object::setDefenseEffect(int value) {}

void Object::setNextPotion(std::shared_ptr<Object> myPotion) {}

std::vector<int> Object::potionBuffers() { 
	std::vector<int> tempVec = { 0, 0 };
	return tempVec;
}

void Object::setKnown() {}

void Object::endTurnEffect() {}

std::shared_ptr<Object> Object::attackEnemy(std::shared_ptr<Object> enemy) { 
	return enemy;
}

bool Object::receiveDmg(int dmg) { return true; } //true if character is alive

void Object::pickPocket() {}

// returns true if player is slain by enemy
bool Object::attackPlayer(std::shared_ptr<Object> player) { return false; }

void Object::resetStatic() {}

void Object::newTurn() {
	hadTurn = false;
}

bool Object::turnCompleted() {
	if (hadTurn == true) { //they had their turn
		return true;
	}
	else { //they didn't have their turn
		hadTurn = true;
		return false;
	}
}

/*
associated object: the below are the 3 scenarios
1. player walks on dragon hoard - it is guarded, so it is underneath the player, not picked up
2. dragon to have an associated object, their hoard
3. hoard to have its associated object (owner), their dragon
the below are functions to get, set, and reset the associated object (associatedObj)
*/
std::shared_ptr<Object> Object::getAssocObject() {
	return this->associatedObj;
}

void Object::setAssocObject(std::shared_ptr<Object> ao) {
	this->associatedObj = ao;
}

void Object::resetAssocObject() {
	this->associatedObj.reset();
}

bool Object::getHostility() {
	return false;
}
