#ifndef __DROW_H__
#define __DROW_H__

#include <string>
#include "player.h"

class Drow : public Player {
	const std::string drowHeroID = "Drow";
	const double potionEffectRate = 1.5;
public:
	Drow(int health, int attack, int defense);
	~Drow();
};

#endif