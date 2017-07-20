#ifndef __ELF_H__
#define __ELF_H__

#include <string>
#include "enemy.h"

class Elf : public Enemy {
	const std::string elfMobID = "Elf";
	const int elfGold = 1;
public:
	Elf(int health, int attack, int defense);
	~Elf();

	bool attackPlayer(Character* player) override;
};

#endif