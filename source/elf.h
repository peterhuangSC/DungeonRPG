#ifndef __ELF_H__
#define __ELF_H__

#include <string>
#include <memory>
#include "enemy.h"

class Elf : public Enemy {
	const std::string elfMobID = "Elf";
	const int elfGold = 1;
public:
	//default stats: Health 140, Attack 30, Defense 10, Gold: 1 pile
	Elf(int health = 140, int attack = 30, int defense = 10);
	~Elf();

	bool attackPlayer(std::shared_ptr<Character> player) override;
};

#endif