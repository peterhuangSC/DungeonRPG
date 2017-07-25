#include <cmath>
#include "drow.h"

using namespace std;

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */
//additional attributes: double potionEffectRate = 1.5
//note: when attaching potions, check to make sure effects are 1.5x

//default stats: health 150, attack 25, defense 15
Drow::Drow(int health, int attack, int defense) :
	Player(health, attack, defense, "drow"),
	potionEffectRate{ 1.5 } {}

Drow::~Drow() {}

void Drow::consumePotion(shared_ptr<Object> myPotion) {
	//case 1: consume health related potions
	if (myPotion->getPotionName().compare("Restore Health") == 0 ||
		myPotion->getPotionName().compare("Poison Health") == 0) {
		this->setHealth(this->getHealth() + potionEffectRate * myPotion->getHealthEffect());
		curAction += " PC consumed a: " + myPotion->getPotionName();
		curAction += ".";
		return;
	}

	myPotion->setAttackEffect(potionEffectRate * myPotion->getAttackEffect());
	myPotion->setDefenseEffect(potionEffectRate * myPotion->getDefenseEffect());

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
