#ifndef __HALFLING_H__
#define __HALFLING_H__

#include <string>
#include "enemy.h"

class Halfling : public Enemy {
	const std::string halflingMobID = "Halfling";
	const int halflingGold = 1;
	const double dodgeRate = 0.5;
public:
	Halfling(int health, int attack, int defense);
	~Halfling();

};

#endif