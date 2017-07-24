#include <string>
#include "goblin.h"

using namespace std;

//additional attributes: const string trollHeroID = "Drow"
//                       const int goldStealRate = 5

//default stats: health 110, attack 15, defense 20
Goblin::Goblin(int health, int attack, int defense) :
	Player(health, attack, defense, "Goblin"),
	goldStealRate{ 5 } {}

Goblin::~Goblin() {}

//this method pickpockets X additional gold for the goblin player upon
//  successfully slain enemy
void Goblin::pickPocket() {
	this->addGold(goldStealRate);
}

// this method performs the attack action
// return val: true if enemy is slain by this attack, false if enemy alive
shared_ptr<Object> Goblin::attackEnemy(shared_ptr<Object> enemy) {
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
			enemy.reset();
			enemy = goldGen.spawnGold('h');
		}
		else if (enemy->getEnemyType().compare("Dragon") == 0) {
			enemy.reset();
			curAction += " The dragon hoard is now unguarded.";
			//add unguard implementation later!
		}
		else if (enemy->getEnemyType().compare("Merchant") == 0) {
			GoldGenerator goldGen;
			curAction += " Merchant drops gold.";
			enemy.reset();
			enemy = goldGen.spawnGold('m');
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
		}
		this->curAction += " PC steals 5 gold.";
		this->pickPocket();
	}
	return enemy;
}
