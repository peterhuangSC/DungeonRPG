#include <string>
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
RestoreHealth::RestoreHealth(shared_ptr<Object> pPlayer) : 
	Potion(pPlayer, "Restore Health", "RH", 10, 0, 0) {}

RestoreHealth::~RestoreHealth() {}

void RestoreHealth::consumePotion(shared_ptr<Object> spPlayer) {
	spPlayer->setHealth(spPlayer->getHealth + healthEffect);
	if (spPlayer->getHeroType().compare("Drow") == 0) {
		spPlayer->setHealth(spPlayer->getHealth + ceil(1.5 * healthEffect));
	}
}

//------------------------POISON HEALTH------------------------//
PoisonHealth::PoisonHealth(shared_ptr<Object> pPlayer) :
	Potion(pPlayer, "Poison Health", "PH", -10, 0, 0) {}

PoisonHealth::~PoisonHealth() {}

void PoisonHealth::consumePotion(shared_ptr<Object> spPlayer) {
	spPlayer->setHealth(spPlayer->getHealth + healthEffect);
	if (spPlayer->getHeroType().compare("Drow") == 0) {
		spPlayer->setHealth(spPlayer->getHealth + floor(1.5 * healthEffect));
	}
}

//------------------------BOOST ATTACK------------------------//
BoostAttack::BoostAttack(shared_ptr<Object> pPlayer) :
	Potion(pPlayer, "Boost Attack", "BA", 0, 5, 0) {}

BoostAttack::~BoostAttack() {}

/* 
if player pointer is empty, this is the first potion the player is consuming
you stack the effects of the potion onto the player's player stats
else if player pointer is not empty, this is NOT the first consumed potion
you stack the effects of the potion onto the previously decorated potion
*/
int BoostAttack::consumePotion() {	
	string thisHero = "";
	thisHero = getAttachedHeroName(player);

	if (thisHero.compare("Drow") == 0) {
		attackEffect = ceil(attackEffect * 1.5);
	}

	if (!player) {
		return player->getAttack() + attackEffect;
	} 
	else {
		return player->consumePotion() + attackEffect;
	}
}


//------------------------WOUND ATTACK------------------------//
WoundAttack::WoundAttack(shared_ptr<Object> pPlayer) :
	Potion(pPlayer, "Wound Attack", "WA", 0, -5, 0) {}

WoundAttack::~WoundAttack() {}

int WoundAttack::consumePotion() {
	string thisHero = "";
	thisHero = getAttachedHeroName(player);

	if (thisHero.compare("Drow") == 0) {
		attackEffect = floor(attackEffect * 1.5);
	}

	if (!player) {
		return player->getAttack() + attackEffect;
	}
	else {
		return player->consumePotion() + attackEffect;
	}
}

//------------------------BOOST DEFENSE------------------------//
BoostDefense::BoostDefense(shared_ptr<Object> pPlayer) :
	Potion(pPlayer, "Boost Defense", "BD", 0, 0, 5) {}

BoostDefense::~BoostDefense() {}

int BoostDefense::consumePotion() {
	string thisHero = "";
	thisHero = getAttachedHeroName(player);

	if (thisHero.compare("Drow") == 0) {
		defenseEffect = ceil(defenseEffect * 1.5);
	}

	if (!player) {
		return player->getDefense() + defenseEffect;
	}
	else {
		return player->consumePotion() + defenseEffect;
	}
}

//------------------------WOUND DEFENSE------------------------//
WoundDefense::WoundDefense(shared_ptr<Object> pPlayer) :
	Potion(pPlayer, "Wound Defense", "WD", 0, 0, -5) {}

WoundDefense::~WoundDefense() {}

int WoundDefense::consumePotion() {
	string thisHero = "";
	thisHero = getAttachedHeroName(player);

	if (thisHero.compare("Drow") == 0) {
		defenseEffect = floor(defenseEffect * 1.5);
	}

	if (!player) {
		return player->getDefense() + defenseEffect;
	}
	else {
		return player->consumePotion() + defenseEffect;
	}
}


