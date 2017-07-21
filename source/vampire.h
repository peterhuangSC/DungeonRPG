#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__

#include <string>
#include <memory>
#include "player.h"

class Vampire : public Player {
	int healthGainRate;
	
public:
	//default stats: health 50, attack 25, defense 25, note also sets max health to 50 to start
	Vampire(int health = 50, int attack = 25, int defense = 25);
	~Vampire();

	void setHealth(int newHealth) override;
	bool attackEnemy(std::shared_ptr<Character> enemy) override;	
};

#endif