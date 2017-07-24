#include "PotionGenerator.h"

using namespace std;

shared_ptr<Potion> PotionGenerator::spawnPotion() {
	int randGen = rand() % 6;
	if (randGen == 0) randGen += 6;

	switch (randGen) {
	case 1: return make_shared<RestoreHealth>();
	case 2: return make_shared<PoisonHealth>();
	case 3: return make_shared<BoostAttack>(nullptr);
	case 4: return make_shared<WoundAttack>(nullptr);
	case 5: return make_shared<BoostDefense>(nullptr);
	case 6: return make_shared<WoundDefense>(nullptr);
	default: return make_shared<RestoreHealth>();
	}

}

shared_ptr<Potion> PotionGenerator::spawnPotion(int type) {
	switch (type) {
	case 1: return make_shared<RestoreHealth>();
	case 2: return make_shared<PoisonHealth>();
	case 3: return make_shared<BoostAttack>(nullptr);
	case 4: return make_shared<WoundAttack>(nullptr);
	case 5: return make_shared<BoostDefense>(nullptr);
	case 6: return make_shared<WoundDefense>(nullptr);
	default: return make_shared<RestoreHealth>();
	}
}

void PotionGenerator::reset(){
	//there are 6 types of potions
	for (int i = 1; i <= 6; i++) {
		spawnPotion(i)->resetStatic();
	}

	/*
	spawnPotion(1)->resetStatic();
	spawnPotion(2)->resetStatic();
	spawnPotion(3)->resetStatic();
	spawnPotion(4)->resetStatic();
	spawnPotion(5)->resetStatic();
	spawnPotion(6)->resetStatic();
	*/
};
