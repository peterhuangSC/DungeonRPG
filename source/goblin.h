#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include <string>
#include <memory>
#include "player.h"

class Goblin : public Player {
	int goldStealRate;
public:
	//default stats: health 110, attack 15, defense 20
	Goblin(int health = 110, int attack = 15, int defense = 20);
	~Goblin();

	void pickPocket();
	bool attackEnemy(std::shared_ptr<Character> p) override;
};

#endif