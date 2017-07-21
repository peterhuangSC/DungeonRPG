#ifndef __ORC_H__
#define __ORC_H__

#include <string>
#include "enemy.h"

class Orc : public Enemy {
	const std::string orcMobID = "Orc";
	const int orcGold = 1;
	const double goblinDamage = 1.5;
public:
	//default stats: Health 180, Attack 30, Defense 25, Gold: 1 pile
	Orc(int health = 180, int attack = 30, int defense = 25);
	~Orc();

	bool attackPlayer(Character* player) override;
};

#endif