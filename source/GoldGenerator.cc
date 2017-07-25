#include "GoldGenerator.h"

using namespace std;

/* Author, Coded & Developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

shared_ptr<Gold> GoldGenerator::spawnGold() {
	shared_ptr<Gold> currentGold;
	int randGen = rand() % 8;
	if (randGen == 0) randGen += 8;

	/*
	Probability Distribution Function of Gold:
	Normal: 5/8, Dragon Hoard: 1/8, Small: 2/8
	
	Values: Small - 1, Normal - 2, Merchant - 4, Dragon Hoard - 6
	Humans drop 2 piles of gold
	Gold parameters: value, quantity, guarded
	*/

	shared_ptr<Gold> dragonHoard = make_shared<Gold>(6, 1, true);
	if (randGen == 5) {		
		EnemyGenerator enemyGen;
		//set the DH's assoc obj to dragon
		dragonHoard->setAssocObject(enemyGen.spawnEnemy('D'));
		//set the dragon's assoc obj to DH
		dragonHoard->getAssocObject()->setAssocObject(dragonHoard);
	}

	switch (randGen) {
	case 1: return make_shared<Gold>(2, 1, false);
	case 2: return make_shared<Gold>(2, 1, false);
	case 3: return make_shared<Gold>(2, 1, false);
	case 4: return make_shared<Gold>(2, 1, false); 
	case 5: return dragonHoard;
		//return make_shared<Gold>(6, 1, true); //DH
	case 6: return make_shared<Gold>(1, 1, false);
	case 7: return make_shared<Gold>(2, 1, false);
	case 8: return make_shared<Gold>(1, 1, false);
	default: return make_shared<Gold>(2, 1, false);
	}

}

/*
This method generates a specific type of gold pile(s) in a tile location with your
specifications. Types: s - small pile, n - normal pile, d - dragon hoard, m - merchant, h - human
*/
shared_ptr<Gold> GoldGenerator::spawnGold(char specificType) {

	shared_ptr<Gold> dragonHoard = make_shared<Gold>(6, 1, true);
	if (specificType == 'd') {
		EnemyGenerator enemyGen;
		//set the DH's assoc obj to dragon
		dragonHoard->setAssocObject(enemyGen.spawnEnemy('D'));
		//set the dragon's assoc obj to DH
		dragonHoard->getAssocObject()->setAssocObject(dragonHoard);
	}

	switch (specificType) {
	case 's': //small pile
		return make_shared<Gold>(1, 1, false);
	case 'n': //normal pile
		return make_shared<Gold>(2, 1, false);
	case 'd': //dragon hoard
		return dragonHoard;
	case 'm': //merchant's gold pile
		return make_shared<Gold>(4, 1, false);
	case 'h': //human 2x gold piles
		return make_shared<Gold>(2, 2, false);
	default:
		//ERROR no such type of gold exists so default generates normal pile
		return make_shared<Gold>(2, 1, false);
	}
}

/*
This method generates a specific type of gold pile(s) in a tile location with your
specifications. 
@@@ 6 - normal gold pile, 7 - small hoard, 8 - merchant hoard, 9 - dragon hoard
*/
shared_ptr<Gold> GoldGenerator::spawnGold(int type) {

	shared_ptr<Gold> dragonHoard = make_shared<Gold>(6, 1, true);
	if (type == 9) {
		EnemyGenerator enemyGen;
		//set the DH's assoc obj to dragon
		dragonHoard->setAssocObject(enemyGen.spawnEnemy('D'));
		//set the dragon's assoc obj to DH
		dragonHoard->getAssocObject()->setAssocObject(dragonHoard);
	}

	switch (type) {	
	case 6: //normal gold pile
		return make_shared<Gold>(2, 1, false);
	case 7: //small pile/hoard
		return make_shared<Gold>(1, 1, false);	
	case 8: //merchant's gold pile/hoard
		return make_shared<Gold>(4, 1, false);
	case 9: //dragon hoard
		return dragonHoard;
	default:
		//ERROR no such type of gold exists so default generates normal pile
		return make_shared<Gold>(2, 1, false);
	}
}


/*
This method generates a specific type of gold pile(s) in a tile location with your
specifications: amount and quantity
*/
shared_ptr<Gold> GoldGenerator::spawnGold(int amount, int quantity) {
	return make_shared<Gold>(amount, quantity, false);
}

void GoldGenerator::reset() {}
