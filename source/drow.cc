#include <cmath>
#include "drow.h"

using namespace std;

//additional attributes: double potionEffectRate = 1.5
//note: when attaching potions, check to make sure effects are 1.5x

//default stats: health 150, attack 25, defense 15
Drow::Drow(int health, int attack, int defense) :
	Player(health, attack, defense, "drow"),
	potionEffectRate{ 1.5 } {}

Drow::~Drow() {}

void Drow::consumePotion(shared_ptr<Object> myPotion) {
	//case 1: consume health related potions
	if (myPotion->getPotionName().compare("Restore Health") ||
		myPotion->getPotionName().compare("Poison Health")) {
		this->setHealth(this->getHealth() + ceil(potionEffectRate * myPotion->getHealthEffect()));
		//remove potion
		return;
	}

	myPotion->setAttackEffect(ceil(potionEffectRate * myPotion->getAttackEffect()));
	myPotion->setDefenseEffect(ceil(potionEffectRate * myPotion->getDefenseEffect()));

	//blue bar for boosted/weakened attack/defense
	if (!potionBuffs) {
		potionBuffs = myPotion;
	}
	else {
		myPotion->setNextPotion(potionBuffs);
		potionBuffs = myPotion;
	}
}
