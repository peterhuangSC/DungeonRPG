#ifndef __SHADE_H__
#define __SHADE_H__

#include <string>
#include "player.h"

class Shade : public Player {
	const std::string shadeHeroID = "Shade";
public:
	Shade(int health, int attack, int defense);
	~Shade();
};

#endif