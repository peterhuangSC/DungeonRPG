#ifndef __SHADE_H__
#define __SHADE_H__

#include <string>
#include "player.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class Shade : public Player {
public:
	Shade(int health = 125, int attack = 25, int defense = 25);
	~Shade();
};

#endif
