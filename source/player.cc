#include <iostream>
#include <cmath>
#include "player.h"
#include "GoldGenerator.h"

using namespace std;

//attributes: curHealth, maxHealth, attack, defense
//            curLevel, gold
//            potions<map> decorator..

//default player is shade
Player::Player(int health, int attack, int defense, string myHeroType) : 
	Character(health, attack, defense, '@'), 
	curLevel{ 1 }, gold{ 0 }, heroType{ myHeroType } {
	//nothing assigned yet for its decorator of potions
	//might need to overload this later
}

Player::~Player() {
	//implementation
}

int Player::getLevel() {
	return this->curLevel;
}

void Player::setLevel(int newLevel) {
	this->curLevel = newLevel;
}

string Player::getHeroType() {
	return this->heroType;
}

int Player::getGold() {
	return this->gold;
}

//this method levels up the player by one level
void Player::levelUp() {
	this->setLevel(this->getLevel() + 1);
	this->potionBuffs.reset(); //reset non-perma potions 
	//implement notification of others like map and enemy?
	//reset potion
}

void Player::addGold(int amount) {
	this->gold += amount;
}

bool Player::addGoldItem(shared_ptr<Object> myGold) {
	if (myGold->isGuarded() == true) {
		curAction += " The gold is guarded, you cannot pick it up.";
		//action: the gold is guarded, you cannot pick it up
		return false;
	}
	int goldQty = myGold->getQuantity(); //number of gold piles in that block
	int goldAmount = myGold->getValue(); //amount of gold per block
	if (goldQty == 1) {
		this->addGold(goldAmount);
		curAction += " PC collected " + to_string(goldAmount);
		curAction += " gold.";
		//action: you have picked up [goldAmount] gold
		return true;
	}
	else if (goldQty > 1) {
		this->addGold(goldAmount * goldQty);
		curAction += " PC collected " + to_string(goldQty);
		curAction += " piles of " + to_string(goldAmount);
		curAction += " gold.";
		//action: you have picked up [goldQty] piles of [goldAmount] gold
		return true;
	}
	else {
		curAction += " PC was unsuccessful at collecting gold.";
		return false;
	}
}

/* this method performs the attack action
   returns a shared pointer:
   1: the enemy passed in if it is still alive
   2: the gold dropped by a human or merchant, if enemy is slain
   2b: in other cases enemy slain will return a reset shared pointer (nullptr) */
shared_ptr<Object> Player::attackEnemy(shared_ptr<Object> enemy) {
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
	
	int myDamage = ceil((100 * trueAttack) / (100 + enemy->getDefense()));
	
	//true if enemy is alive after receiving the damage you just dealt
	bool isEnemyAlive = enemy->receiveDmg(myDamage);
	curAction = " PC deals " + to_string(myDamage);
	curAction += " damage to " + enemy->getEnemyType();
	curAction += " (" + to_string(enemy->getHealth());
	curAction += " HP).";

	if (isEnemyAlive) {
		return enemy;
	}
	else {
		curAction += " " + enemy->getEnemyType();
		curAction += " is slain.";
		if (enemy->getEnemyType().compare("Human") == 0) {
			GoldGenerator goldGen;
			curAction += " Human drops gold.";
			return goldGen.spawnGold('h');
		}
		else if (enemy->getEnemyType().compare("Dragon") == 0) {
			enemy.reset();
			curAction += " The dragon hoard is now unguarded.";
			//add unguard implementation later!
			return enemy;
		}
		else if (enemy->getEnemyType().compare("Merchant") == 0) {
			GoldGenerator goldGen;
			curAction += " Merchant drops gold.";
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

/*
PSEUDO CODE
Basically, in floor or map, you have cells linked to each enemy object. If the enemy
is slain, the above method returns true. You can then use that boolean variable in a
if statement, to perform the below commands.
1. remove enemy from current cell
2. int randGoldAmount = rand() % 2 [DONE]
3. if (randGoldAmount == 1) player->gold += 1 [DONE]
4. else player->gold += 2; [DONE]
*/


void Player::notifyObservers() {
	cerr << "Notify Observers under construction" << endl;
}
