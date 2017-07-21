#ifndef __DROW_H__
#define __DROW_H__

#include <string>
#include "player.h"

class Drow : public Player {
	const std::string drowHeroID = "Drow";
	const double potionEffectRate = 1.5;
public:
	Drow(int health = 150, int attack = 25, int defense = 15);
	~Drow();
};

#endif