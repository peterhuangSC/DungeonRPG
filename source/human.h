#ifndef __HUMAN_H__
#define __HUMAN_H__

#include <string>
#include "enemy.h"

class Human : public Enemy {

public:
	//default stats: Health 140, Attack 20, Defense 20, Gold: 2 piles
	Human(int health = 140, int attack = 20, int defense = 20);
	~Human();	
};

#endif
