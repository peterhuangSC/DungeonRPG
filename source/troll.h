#ifndef __TROLL_H__
#define __TROLL_H__

#include <string>
#include "player.h"

class Troll : public Player {
	const std::string trollHeroID = "Troll";
	const int healthGainRate = 5;

public:
	Troll(int health, int attack, int defense);
	~Troll();
};

#endif