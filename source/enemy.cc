#include <string>
#include <iostream>
#include <cmath>
#include "enemy.h"

using namespace std;

//attributes: curHealth, maxHealth, attack, defense
//            enemyLevel, goldDrop, isHostile, isMovable


//default enemy is human
Enemy::Enemy(int health, int attack, int defense, string myEnemyType, char mapSymbol) : 
	Character(health, attack, defense, mapSymbol), 
	enemyLevel{ 1 }, enemyType{ myEnemyType }, 
	isHostile { true }, isMovable{ true } {}

Enemy::~Enemy() {
	//implementation
}

int Enemy::getLevel() {
	return this->enemyLevel;
}

void Enemy::setLevel(int newLevel) {
	this->enemyLevel = newLevel;
}

string Enemy::getEnemyType() {
	return this->enemyType;
}

void Enemy::levelUp() {
	this->setLevel(this->getLevel() + 1);
}

void Enemy::severTies() {
	this->isHostile = true;
}

// this method performs the attack action
// return val: true if player(opponent) is slain by this attack, false if player is alive
bool Enemy::attackPlayer(shared_ptr<Character> player) {
	if (!player) return false;
	
	int accuracyRoll = rand() % 2;

	if (accuracyRoll == 0) return false;
	//else accuracyRoll == 1, proceed with the attack => enemy doesn't miss

	//computing player's true defense
	int defIndex = 1;
	int truePlayerDef = player->getDefense();
	if (player->getPotionBuffs()) {
		truePlayerDef += player->getPotionBuffs()->potionBuffers()[defIndex];
	}
	if (truePlayerDef < 0) truePlayerDef = 0;
	
	int myDamage = ceil((100 / (100 + truePlayerDef) * this->getAttack()));

	//true if enemy is alive after receiving the damage you just dealt
	bool isPlayerAlive = player->receiveDmg(myDamage);

	if (isPlayerAlive) {
		//check others like: isAlive method
		return false;
	}
	else {
		return true;
	}
}

void Enemy::dropGold() {
	cerr << "Under construction" << endl;
	// use enemy generator and generate the correct amount of gold, let this be overriden
}

void Enemy::notifyObservers() {
	cerr << "Notify Observers under construction" << endl;
}

bool Enemy::canMove() {
	return true;

	//might do this implementation later
	//if (isMovable) return true;
	//else return false;
}
