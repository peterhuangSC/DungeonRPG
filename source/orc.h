#ifndef __ORC_H__
#define __ORC_H__

#include <string>
#include "enemy.h"

class Orc : public Enemy {
	const std::string orcMobID = "Orc";
	const int orcGold = 1;
	const double goblinDamage = 1.5;
public:
	Orc(int health, int attack, int defense);
	~Orc();

	bool attackPlayer(Character* player) override;
};

#endif