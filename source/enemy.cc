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
bool Enemy::attackPlayer(shared_ptr<Object> player) {
	if (!player) return false;
	
	int accuracyRoll = rand() % 2;

	if (accuracyRoll == 0) { 
		player->appendAction(" " + this->getEnemyType());
		player->appendAction(" misses attack on PC.");
		return false; 
	}
	//else accuracyRoll == 1, proceed with the attack => enemy doesn't miss

	//computing player's true defense
	int truePlayerDef = player->getDefense();
	
	int myDamage = ceil((100 * this->getAttack())/ (100 + truePlayerDef));

	//true if enemy is alive after receiving the damage you just dealt
	bool isPlayerAlive = player->receiveDmg(myDamage);
	

	player->appendAction(" PC receives " + to_string(myDamage));
	player->appendAction(" damage from " + this->getEnemyType());
	player->appendAction(".");

	if (isPlayerAlive) {
		return false;
	}
	else {
		player->appendAction(" PC is slain by " + this->getEnemyType());
		player->appendAction(".");
		return true;
	}
}

void Enemy::notifyObservers() {
	//cerr << "This function is out of date - this fn should not be used." << endl;
	//cerr << "Peter Huang and Shane Mazur (C) 2017." << endl;
}

bool Enemy::canMove() {
	//cerr << "This function is out of date - this fn should not be used." << endl;
	//cerr << "Peter Huang and Shane Mazur (C) 2017." << endl;
	return true;	
}

bool Enemy::getHostility() {
	return this->isHostile;
}
