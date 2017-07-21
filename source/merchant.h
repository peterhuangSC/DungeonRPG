#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include <string>
#include "enemy.h"

class Merchant : public Enemy {

public:
	//default stats: Health 30, Attack 70, Defense 5, <Gold: 1 pile?? check this>
	Merchant(int health = 30, int attack = 70, int defense = 5);
	~Merchant();

	//bool attackPlayer(Character* player) override;
	//severTies() already exists from the superclass
};

#endif