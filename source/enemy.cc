#include <string>
#include <iostream>
#include <map>
#include <cmath>
#include "enemy.h"

using namespace std;

//attributes: curHealth, maxHealth, attack, defense
//            enemyLevel, goldDrop, isHostile, isMovable


//default enemy is human
Enemy::Enemy(int health = 140, int attack = 20, int defense = 20, 
	string myEnemyType = "Human", int goldDrop = 2, char mapSymbol = 'H') : 
	Character(health, attack, defense, mapSymbol), 
	enemyLevel{ 1 }, goldDrop{ 2 },	enemyType{ myEnemyType }, 
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
bool Enemy::attackPlayer(Character* player) {
	int accuracyRoll = rand() % 2;

	if (accuracyRoll == 0) return false;
	//else accuracyRoll == 1, proceed with the attack => enemy doesn't miss
	
	int myDamage = ceil((100 / (100 + player->getDefense()) * this->getAttack()));

	//true if enemy is alive after receiving the damage you just dealt
	bool isPlayerAlive = player->receiveDmg(myDamage);

	if (isPlayerAlive) {
		return false;
	}
	else {
		return true;
	}
}

void Enemy::dropGold() {
	cerr << "Under construction" << endl;
	cerr << "Dropping " << this->goldDrop << " amount of gold!" << endl;
}

void Enemy::notifyObservers() {
	cerr << "Notify Observers under construction" << endl;
}