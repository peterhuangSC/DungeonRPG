#ifndef __TROLL_H__
#define __TROLL_H__

#include <string>
#include <algorithm>
#include "player.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class Troll : public Player {
	int healthGainRate;

public:
	//default stats: health 120, attack 25, defense 15
	Troll(int health = 120, int attack = 25, int defense = 15);
	~Troll();

	void endTurnEffect() override;
};

#endif
