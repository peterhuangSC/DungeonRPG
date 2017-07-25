#ifndef __MERCHANT_H__
#define __MERCHANT_H__

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

#include <string>
#include "enemy.h"

class Merchant : public Enemy {
	static bool mercHostile;

public:
	//default stats: Health 30, Attack 70, Defense 5, <Gold: 1 pile?? check this>
	Merchant(int health = 30, int attack = 70, int defense = 5);
	~Merchant();

	bool canMove() override;

	bool receiveDmg(int dmg) override;

	//severTies() already exists from the superclass

	void resetStatic() override;
	bool getHostility() override;
};

#endif
