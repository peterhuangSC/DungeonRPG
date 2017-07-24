#include <string>
#include <cmath>
#include "dwarf.h"

//additional attributes: const string dwarfMobID = "Dwarf", const int dwarfGold = 1

//default stats: Health 100, Attack 20, Defense 30, Gold: 1 pile
Dwarf::Dwarf(int health, int attack, int defense) :
	Enemy(health, attack, defense, "Dwarf", 'W') {

	this->isMovable = true;
	this->isHostile = true;

	this->enemyLevel = 1;
}

Dwarf::~Dwarf() {}
