#include <string>
#include <iostream>
#include <cmath>
#include "vampire.h"

using namespace std;

//additional attributes: const string drowHeroID = "Drow", potionEffectRate = 1.5
// const int healthGainRate = 5;

//default stats: health 50, attack 25, defense 25, note also sets max health to 50 to start
Vampire::Vampire(int health = 50, int attack = 25, int defense = 25) :
	Player(health, attack, defense, vampireHeroID) {}

Vampire::~Vampire() {}

//overriden method of setHealth as the maxHealth is NOT capped
void Vampire::setHealth(int newHealth) {
	this->curHealth = newHealth;
	//increasing maxHealth
	if (this->curHealth > this->maxHealth) {
		this->maxHealth = this->curHealth;
		//IMPORTANT, potions are decorators so they should not affect this..
		//BUT remember to NOT increase maxHealth when potions are consumed..
	}
}

// this method performs the attack action
// return val: true if enemy is slain by this attack, false if enemy alive
bool Vampire::attackEnemy(Character* enemy) {
	if (enemy->getEnemyType().compare("Halfling") == 0) {
		int halflingDodgeCheck = rand() % 2;
		if (halflingDodgeCheck == 0) {
			return false; //enemy is still alive (not slain), you missed your attack!
		}
	}

	int myDamage = ceil((100 / (100 + enemy->getDefense()) * this->getAttack()));

	if (enemy->getEnemyType().compare("Dwarf") == 0) {
		this->setHealth(this->getHealth() - healthGainRate);
		if (this->curHealth <= 0) {
			cerr << "You have died from sucking blood, WIP" << endl;
			//invoke slain method if vampire dies from this lol
		}		
	}
	else {
		this->setHealth(this->getHealth() + healthGainRate);
	}

	//true if enemy is alive after receiving the damage you just dealt
	bool isEnemyAlive = enemy->receiveDmg(myDamage);

	if (isEnemyAlive) {
		return false;
	}
	else {
		return true;
	}
}