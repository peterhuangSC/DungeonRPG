#ifndef __ORC_H__
#define __ORC_H__

#include <string>
#include <memory>
#include "enemy.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class Orc : public Enemy {

	double goblinDamage;
public:
	//default stats: Health 180, Attack 30, Defense 25, Gold: 1 pile
	Orc(int health = 180, int attack = 30, int defense = 25);
	~Orc();

	bool attackPlayer(std::shared_ptr<Object> player) override;
};

#endif
