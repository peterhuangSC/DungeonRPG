#include <string>
#include "object.h"

Object::Object(char typeSymbol) : type{ typeSymbol } {
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

int Object::getHealth() { return -1; }
void Object::setHealth(int newHealth) {}

int Object::getAttack() { return -1; }

int Object::getDefense() { return -1; }

int Object::getHealthEffect() { return 0; }

int Object::getAttackEffect() { return 0; }

int Object::getDefenseEffect() { return 0; }

int Object::getLevel() { return 1; }
void Object::levelUp() {}
int Object::getGold() {}
void Object::addGold(int myGold) {}

void Object::notify(std::shared_ptr<Object> who) {
	// to be implemented
}

int Object::consumePotion() {
	//no default implemetation required
	//implementation is only required in Player and Potion classes
}

void Object::consumePotion(std::shared_ptr<Object> myObj) {}

bool Object::consumeGold(std::shared_ptr<Object> myObj) {}

void Object::consumeLadder(std::shared_ptr<Object> player) {}
