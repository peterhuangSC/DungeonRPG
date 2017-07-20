#ifndef __DRAGON_H__
#define __DRAGON_H__

#include <string>
#include "enemy.h"

class Dragon : public Enemy {
	const std::string dragonMobID = "Dragon";
	const int dragonGold = 1;
public:
	Dragon(int health, int attack, int defense);
	~Dragon();

};

#endif