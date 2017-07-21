#ifndef __TROLL_H__
#define __TROLL_H__

#include <string>
#include "player.h"

class Troll : public Player {
	const std::string trollHeroID = "Troll";
	const int healthGainRate = 5;

public:
	//default stats: health 120, attack 25, defense 15
	Troll(int health = 120, int attack = 25, int defense = 15);
	~Troll();
};

#endif