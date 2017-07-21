#include <string>
#include <cmath>
#include "specificPotions.h"

using namespace std;

/*
ATTRIBUTES: (protected)

<in Potion>
shared pointer player
string potionID, int healthEffect, int attackEffect, int defenseEffect
mapSymbol (item), type (object)
*/

// Constructor for Potion Layout: 
// PotionName, PotionID, HealthEff, AttackEff, DefenseEff

//------------------------RESTORE HEALTH------------------------//
RestoreHealth::RestoreHealth() : 
	Potion(nullptr, "Restore Health", "RH", 10, 0, 0) {}

RestoreHealth::~RestoreHealth() {}

//------------------------POISON HEALTH------------------------//
PoisonHealth::PoisonHealth() :
	Potion(nullptr, "Poison Health", "PH", -10, 0, 0) {}

PoisonHealth::~PoisonHealth() {}

//------------------------BOOST ATTACK------------------------//
BoostAttack::BoostAttack(shared_ptr<Potion> np) :
	Potion(np, "Boost Attack", "BA", 0, 5, 0) {}

BoostAttack::~BoostAttack() {}

vector<int> BoostAttack::potionBuffers() {	
	/*
	string thisHero = "";
	thisHero = getAttachedHeroName(player);

	if (thisHero.compare("Drow") == 0) {
		attackEffect = ceil(attackEffect * 1.5);
	}
	*/
	vector<int> additionalStats = {attackEffect, 0};

	if (nextPotion){
		additionalStats[0] += nextPotion->potionBuffers()[0];
		additionalStats[1] += nextPotion->potionBuffers()[1];
	}
	return additionalStats;
}


//------------------------WOUND ATTACK------------------------//
WoundAttack::WoundAttack(shared_ptr<Potion> np) :
	Potion(np, "Wound Attack", "WA", 0, -5, 0) {}

WoundAttack::~WoundAttack() {}

vector<int> WoundAttack::potionBuffers() {
	vector<int> additionalStats = { attackEffect, 0 };

	if (nextPotion) {
		additionalStats[0] += nextPotion->potionBuffers()[0];
		additionalStats[1] += nextPotion->potionBuffers()[1];
	}
	return additionalStats;
}

//------------------------BOOST DEFENSE------------------------//
BoostDefense::BoostDefense(shared_ptr<Potion> np) :
	Potion(np, "Boost Defense", "BD", 0, 0, 5) {}

BoostDefense::~BoostDefense() {}

vector<int> BoostDefense::potionBuffers() {
	vector<int> additionalStats = { 0, defenseEffect };

	if (nextPotion) {
		additionalStats[0] += nextPotion->potionBuffers()[0];
		additionalStats[1] += nextPotion->potionBuffers()[1];
	}
	return additionalStats;
}

//------------------------WOUND DEFENSE------------------------//
WoundDefense::WoundDefense(shared_ptr<Potion> np) :
	Potion(np, "Wound Defense", "WD", 0, 0, -5) {}

WoundDefense::~WoundDefense() {}

vector<int> WoundDefense::potionBuffers() {
	vector<int> additionalStats = { 0, defenseEffect };

	if (nextPotion) {
		additionalStats[0] += nextPotion->potionBuffers()[0];
		additionalStats[1] += nextPotion->potionBuffers()[1];
	}
	return additionalStats;
}


