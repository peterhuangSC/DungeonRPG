#include "GoldGenerator.h"

using namespace std;

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

	switch (randGen) {
	case 1: return make_shared<Gold>(2, 1, false);
	case 2: return make_shared<Gold>(2, 1, false);
	case 3: return make_shared<Gold>(2, 1, false);
	case 4: return make_shared<Gold>(2, 1, false); 
	case 5: return make_shared<Gold>(6, 1, true); //DH
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
	switch (specificType) {
	case 's': //small pile
		return make_shared<Gold>(1, 1, false);
	case 'n': //normal pile
		return make_shared<Gold>(2, 1, false);
	case 'd': //dragon hoard
		return make_shared<Gold>(6, 1, true);
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
specifications: amount and quantity
*/
shared_ptr<Gold> GoldGenerator::spawnGold(int amount, int quantity) {
	return make_shared<Gold>(amount, quantity, false);
}

