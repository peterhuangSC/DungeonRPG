#ifndef __DRAGON_H__
#define __DRAGON_H__

#include <string>
#include "enemy.h"

class Dragon : public Enemy {

public:
	//default stats: Health 150, Attack 20, Defense 20, Gold: 1 pile
	Dragon(int health = 150, int attack = 20, int defense = 20);
	~Dragon();
		
	bool canMove() override;

	bool receiveDmg(int dmg) override;
};

#endif
