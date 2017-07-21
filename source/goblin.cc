#include <string>
#include "goblin.h"

using namespace std;

//additional attributes: const string trollHeroID = "Drow"
//                       const int goldStealRate = 5

//default stats: health 110, attack 15, defense 20
Goblin::Goblin(int health, int attack, int defense) :
	Player(health, attack, defense, "Goblin") {}

Goblin::~Goblin() {}

//this method pickpockets X additional gold for the goblin player upon
//  successfully slain enemy
void Goblin::pickPocket() {
	this->addGold(goldStealRate);
}

// this method performs the attack action
// return val: true if enemy is slain by this attack, false if enemy alive
bool Goblin::attackEnemy(shared_ptr<Character> enemy) {
	bool isEnemySlain = false;
	
	//step 1 attack enemy as original, as well as get if enemy slain or not
	isEnemySlain = Player::attackEnemy(enemy);

	if (isEnemySlain) {
		this->pickPocket();
	}
	return isEnemySlain;
}

