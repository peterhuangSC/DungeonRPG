#ifndef __HALFLING_H__
#define __HALFLING_H__

#include <string>
#include "enemy.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class Halfling : public Enemy {
	double dodgeRate;
public:
	//default stats: Health 100, Attack 15, Defense 20, Gold: 1 pile
	Halfling(int health = 100, int attack = 15, int defense = 20);
	~Halfling();
};

#endif
