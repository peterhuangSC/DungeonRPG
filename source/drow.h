#ifndef __DROW_H__
#define __DROW_H__

#include <memory>
#include "player.h"

class Drow : public Player {
	double potionEffectRate;
public:
	//default stats: health 150, attack 25, defense 15
	Drow(int health = 150, int attack = 25, int defense = 15);
	~Drow();

	void consumePotion(std::shared_ptr<Potion> myPotion) override;
};

#endif
