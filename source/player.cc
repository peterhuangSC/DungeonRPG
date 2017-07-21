#include <iostream>
#include <cmath>
#include "player.h"

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
	//implement notification of others like map and enemy?
	//reset potion decorators
}

void Player::addGold(int amount) {
	this->gold += amount;
}

// this method performs the attack action
// return val: true if enemy is slain by this attack, false if enemy alive
bool Player::attackEnemy(shared_ptr<Character> enemy) {

	if (enemy->getEnemyType().compare("Halfling") == 0) {
		int halflingDodgeCheck = rand() % 2;
		if (halflingDodgeCheck == 0) {
			return false; //enemy is still alive (not slain), you miss your attack
		}
	}
	
	int myDamage = ceil((100 / (100 + enemy->getDefense()) * this->getAttack()));
	
	//true if enemy is alive after receiving the damage you just dealt
	bool isEnemyAlive = enemy->receiveDmg(myDamage);

	if (isEnemyAlive) {
		return false;
	}
	else if (enemy->getEnemyType().compare("Human")) {
	}
	else if (enemy->getEnemyType().compare("Dragon")) {
	}
	else if (enemy->getEnemyType().compare("Merchant")) {
	} 
	else {
		//enemy has been slain
		int randGoldAmount = rand() % 2;
		if (randGoldAmount == 1) this->addGold(2);
		else this->addGold(1);
		return true;
	}
	return false;
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


void Player::move(string direction) {
	//use coordinates structure here 
	//might need to pass in an instance of grid and check if valid
	//check if needs equals ignore case
	if (direction == "nw") {
		//check if anything is occupying space and the space is a valid tile
	}
	else if (direction == "no") {
		/*Implementation*/
	}
	else if (direction == "ne") {
		/*Implementation*/
	}
	else if (direction == "ea") {
		/*Implementation*/
	}
	else if (direction == "se") {
		/*Implementation*/
	}
	else if (direction == "so") {
		/*Implementation*/
	}
	else if (direction == "sw") {
		/*Implementation*/
	}
	else if (direction == "we") {
		/*Implementation*/
	}

}

void Player::notifyObservers() {
	cerr << "Notify Observers under construction" << endl;
}