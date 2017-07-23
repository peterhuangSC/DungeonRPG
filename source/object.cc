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
std::string Object::getEnemyType() {
	return "Object";
};

int Object::getHealth() { return -1; }
void Object::setHealth(int newHealth) {}

int Object::getAttack() { return -1; }

int Object::getDefense() { return -1; }

int Object::getLevel() { return 1; }
void Object::levelUp() {} //overriden in player - increase level and delete buffer potions
int Object::getGold() { return -1; }
void Object::addGold(int myGold) {}

void Object::notify(std::shared_ptr<Object> who) {
	// to be implemented
}

bool Object::consumeGold(std::shared_ptr<Object> myObj) { return false; }

void Object::consumeLadder(std::shared_ptr<Object> player) {}

bool Object::isGuarded() { return false; }

void Object::setGuarded() {}
void Object::setUnguarded() {}

std::string Object::getAction() {
	return "n/a";
}
void Object::setAction(std::string newAction) {}
