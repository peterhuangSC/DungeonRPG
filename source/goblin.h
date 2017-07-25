#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include <string>
#include <memory>
#include "player.h"
#include "GoldGenerator.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class Goblin : public Player {
	int goldStealRate;
public:
	//default stats: health 110, attack 15, defense 20
	Goblin(int health = 110, int attack = 15, int defense = 20);
	~Goblin();

	void pickPocket() override;
	std::shared_ptr<Object> attackEnemy(std::shared_ptr<Object> p) override;
};

#endif
