#ifndef __DRAGON_H__
#define __DRAGON_H__

#include <string>
#include "enemy.h"

class Dragon : public Enemy {
	const std::string dragonMobID = "Dragon";
	const int dragonGold = 1;
public:
	//default stats: Health 150, Attack 20, Defense 20, Gold: 1 pile
	Dragon(int health = 150, int attack = 20, int defense = 20);
	~Dragon();

};

#endif