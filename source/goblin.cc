#include <string>
#include "goblin.h"

using namespace std;

//additional attributes: const string trollHeroID = "Drow"
//                       const int goldStealRate = 5

//default stats: health 110, attack 15, defense 20
Goblin::Goblin(int health = 110, int attack = 15, int defense = 20) :
	Player(health, attack, defense, goblinHeroID) {}

Goblin::~Goblin() {}

//this method pickpockets X additional gold for the goblin player upon
//  successfully slain enemy
void Goblin::pickPocket() {
	this->addGold(goldStealRate);
}

// this method performs the attack action
// return val: true if enemy is slain by this attack, false if enemy alive
bool Goblin::attackEnemy(Character* enemy) {
	bool isEnemySlain = false;
	
	//step 1 attack enemy as original, as well as get if enemy slain or not
	isEnemySlain = Player::attackEnemy(enemy);

	if (isEnemySlain) {
		this->pickPocket();
	}
	return isEnemySlain;
}

