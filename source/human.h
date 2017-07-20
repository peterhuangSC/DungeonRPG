#ifndef __HUMAN_H__
#define __HUMAN_H__

#include <string>
#include "enemy.h"

class Human : public Enemy {
	const std::string humanMobID = "Human";
	const int humanGold = 2;
public:
	Human(int health, int attack, int defense);
	~Human();
	
};

#endif