#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include <string>
#include "player.h"

class Goblin : public Player {
	const std::string goblinHeroID = "Goblin";
	const int goldStealRate = 5;
public:
	Goblin(int health, int attack, int defense);
	~Goblin();

	void pickPocket();
	bool attackEnemy(Character* p) override;
};

#endif