#ifndef __DWARF_H__
#define __DWARF_H__

#include <string>
#include "enemy.h"

class Dwarf : public Enemy {
	const std::string dwarfMobID = "Dwarf";
	const int dwarfGold = 1;
public:
	Dwarf(int health = 100, int attack = 20, int defense = 30);
	~Dwarf();

};

#endif