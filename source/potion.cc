#include <string>
#include "potion.h"

using namespace std;

/*
ATTRIBUTES: (protected)
  string potionID, int healthEffect, int attackEffect, int defenseEffect
  mapSymbol (item), type (object)
*/

Potion::Potion(shared_ptr<Object> pPlayer, string potName = "No Effect Potion", 
	string id = "NEFF", int hEff = 0, int aEff = 0, int dEff = 0) : 
	Item('P'), player{ pPlayer }, potionName { potName }, potionID{ id },
	healthEffect { hEff }, attackEffect{ aEff }, defenseEffect{ dEff } {}

Potion::~Potion() {}

char Potion::getType() {
	//if (pointer not null) this potion is decorated on a player	
	if (player) return '@';
	//else if the pointer is null then it is a potion that hasn't been picked up
	else return 'P';
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

//---------------------------helper-----------------------------//

std::string Potion::getAttachedHeroName(std::shared_ptr<Object> myObj) {
	if (myObj.get() == nullptr) { return "NULLHERO"; }
	else if (myObj->getType == '@') {
		return myObj->getHeroType();
	}
	else if (myObj->getType == 'P') {
		std::string heroName = getAttachedHeroName(player);
		return heroName;
	}
}