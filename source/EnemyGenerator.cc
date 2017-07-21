#include "EnemyGenerator.h"

using namespace std;

shared_ptr<Enemy> spawnEnemy() {
	shared_ptr<Enemy> currentEnemy;
	int randGen = rand() % 18;
	if (randGen == 0) randGen += 18;

	/*
	Probability Distribution Function:
	Human: 4/18, Dwarf: 3/18, Halfling: 5/18, Elf: 2/18, Orc: 2/18, Merchant: 2/18
	*/

	switch (randGen) {
	case 1: return make_shared<Human>();
	case 2: return make_shared<Human>();
	case 3: return make_shared<Human>();
	case 4: return make_shared<Human>();
	case 5: return make_shared<Dwarf>();
	case 6: return make_shared<Dwarf>();
	case 7: return make_shared<Dwarf>();
	case 8: return make_shared<Halfling>();
	case 9: return make_shared<Halfling>();
	case 10: return make_shared<Halfling>();
	case 11: return make_shared<Halfling>();
	case 12: return make_shared<Halfling>();
	case 13: return make_shared<Elf>();
	case 14: return make_shared<Elf>();
	case 15: return make_shared<Orc>();
	case 16: return make_shared<Orc>();
	case 17: return make_shared<Merchant>();
	case 18: return make_shared<Merchant>();
	default: return make_shared<Halfling>();
	}

}

shared_ptr<Enemy> spawnEnemy(char specificType) {
	switch (specificType) {
	case 'H': //human
		return make_shared<Human>();
	case 'W': //dwarf
		return make_shared<Dwarf>();
	case 'E': //elf
		return make_shared<Elf>();
	case 'O': //orc
		return make_shared<Orc>();
	case 'M': //merchant
		return make_shared<Merchant>();
	case 'D': //dragon
		return make_shared<Dragon>();
	case 'L': //halfling
		return make_shared<Halfling>();
	default:
		//ERROR no such class exists but whatever here's a human enemy
		return make_shared<Human>();
	}
}