#include <string>
#include <iostream>
#include <cmath>
#include "vampire.h"

using namespace std;

//additional attributes: const string drowHeroID = "Drow", potionEffectRate = 1.5
// const int healthGainRate = 5;

//default stats: health 50, attack 25, defense 25, note also sets max health to 50 to start
Vampire::Vampire(int health, int attack, int defense) :
	Player(health, attack, defense, "vampire"), 
	healthGainRate{ 5 } {}

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
shared_ptr<Object> Vampire::attackEnemy(shared_ptr<Object> enemy) {
	if (!enemy) return enemy;

	//this below is your TRUE ATTACK
	int trueAttack = this->getAttack();

	if (enemy->getEnemyType().compare("Halfling") == 0) {
		int halflingDodgeRand = rand() % 2;
		if (halflingDodgeRand == 0) {
			curAction = " PC misses attack on Halfling.";
			return enemy; //enemy is still alive (not slain), you miss your attack
		}
	}

	int myDamage = ceil((100 / (100 + enemy->getDefense()) * trueAttack));

	if (enemy->getEnemyType().compare("Dwarf") == 0) {
		this->setHealth(this->getHealth() - healthGainRate);
		this->curAction += " PC loses " + to_string(healthGainRate);
		this->curAction += " HP from attacking Dwarf.";
		if (this->curHealth <= 0) {
			this->curHealth = 0;
			this->curAction += " PC dies from attacking Dwarf.";
			return enemy; //#peter: @shane then deal with ending the game b/c PC died
		}
	}
	else {
		this->curAction += " PC gains " + to_string(healthGainRate);
		this->curAction += " HP from attack.";
		this->setHealth(this->getHealth() + healthGainRate);
	}

	//true if enemy is alive after receiving the damage you just dealt
	bool isEnemyAlive = enemy->receiveDmg(myDamage);
	curAction = " PC deals " + to_string(myDamage);
	curAction += " damage to " + enemy->getEnemyType();

	if (isEnemyAlive) {
		return enemy;
	}
	else {
		curAction += " " + enemy->getEnemyType();
		curAction += " has been slain by PC.";
		if (enemy->getEnemyType().compare("Human")) {
			GoldGenerator goldGen;
			curAction += " Human drops some gold.";
			return goldGen.spawnGold('h');
		}
		else if (enemy->getEnemyType().compare("Dragon")) {
			enemy.reset();
			curAction += " The dragon hoard is now unguarded.";
			//add unguard implementation later!
			return enemy;
		}
		else if (enemy->getEnemyType().compare("Merchant")) {
			GoldGenerator goldGen;
			curAction += " Merchant drops some gold.";
			return goldGen.spawnGold('m');
		}
		else {
			//enemy has been slain
			int randGoldAmount = (rand() % 2) + 1;
			this->addGold(randGoldAmount);
			curAction += " PC receives " + to_string(randGoldAmount);
			curAction += " gold from ";
			curAction += enemy->getEnemyType() + ".";
			//pg3 specifications, 2.2, GOLD IS IMMEDIATELY ADDED TO PLAYER'S TOTAL
			enemy.reset();
			return enemy;
		}
	}
	return enemy;
}
