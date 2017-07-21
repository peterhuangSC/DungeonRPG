#ifndef __SHADE_H__
#define __SHADE_H__

#include <string>
#include "player.h"

class Shade : public Player {
public:
	Shade(int health = 125, int attack = 25, int defense = 25);
	~Shade();
};

#endif