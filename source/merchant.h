#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include <string>
#include "enemy.h"

class Merchant : public Enemy {
	const std::string merchantMobID = "Merchant";
	const int merchantGold = 4;
public:
	Merchant(int health, int attack, int defense);
	~Merchant();

	//bool attackPlayer(Character* player) override;
	//severTies() already exists from the superclass
};

#endif