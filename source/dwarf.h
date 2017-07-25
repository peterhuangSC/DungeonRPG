#ifndef __DWARF_H__
#define __DWARF_H__

#include <string>
#include "enemy.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class Dwarf : public Enemy {

public:
	//default stats: Health 100, Attack 20, Defense 30, Gold: 1 pile
	Dwarf(int health = 100, int attack = 20, int defense = 30);
	~Dwarf();
};

#endif
