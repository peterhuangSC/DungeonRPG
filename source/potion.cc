#include <string>
#include "potion.h"

using namespace std;

/*
ATTRIBUTES: (protected)
  string potionID, int healthEffect, int attackEffect, int defenseEffect
  mapSymbol (item), type (object)
*/

Potion::Potion(shared_ptr<Potion> nxtPotion, string potName, string id,
	int hEff, int aEff, int dEff) :	Item('P'), 
	nextPotion{ nxtPotion }, potionName { potName }, potionID{ id },
	healthEffect { hEff }, attackEffect{ aEff }, defenseEffect{ dEff } {}

Potion::~Potion() {}

char Potion::getType() {
	return 'P';
}

int Potion::getHealthEffect() {
	return this->healthEffect;
}

int Potion::getAttackEffect() {
	return this->attackEffect;
}

int Potion::getDefenseEffect() {
	return this->defenseEffect;
}

void Potion::setAttackEffect(int value) {
	this->attackEffect = value;
}

void Potion::setDefenseEffect(int value) {
	this->defenseEffect = value;
}

string Potion::getPotionName() {
	return this->potionName;
}

void Potion::setNextPotion(shared_ptr<Object> myPotion) {
	this->nextPotion = myPotion;
}

vector<int> Potion::potionBuffers() {
	vector<int> myPotBuf = { 0, 0 };
	return myPotBuf;
}

void Potion::notify(shared_ptr<Object> player) {
	player->appendAction(" PC sees an unknown potion.");
}

//---------------------------helper-----------------------------//

/*
This is kind of obsolete right now, might come in handy later
std::string Potion::getAttachedHeroName(std::shared_ptr<Object> myObj) {
	if (myObj.get() == nullptr) { return "NULLHERO"; }
	else if (myObj->getType() == '@') {
		return myObj->getHeroType();
	}
	else if (myObj->getType() == 'P') {
		std::string heroName = getAttachedHeroName(player);
		return heroName;
	}
	return "Hero name not set!";
}
*/
