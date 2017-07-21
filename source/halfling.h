#ifndef __HALFLING_H__
#define __HALFLING_H__

#include <string>
#include "enemy.h"

class Halfling : public Enemy {
	const std::string halflingMobID = "Halfling";
	const int halflingGold = 1;
	const double dodgeRate = 0.5;
public:
	//default stats: Health 100, Attack 15, Defense 20, Gold: 1 pile
	Halfling(int health = 100, int attack = 15, int defense = 20);
	~Halfling();

};

#endif