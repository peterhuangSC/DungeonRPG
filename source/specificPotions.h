#ifndef __SPECIFIC_POTIONS_H__
#define __SPECIFIC_POTIONS_H__

#include <string>
#include <memory>
#include "potion.h"

class RestoreHealth : public Potion {
public:
	RestoreHealth(std::shared_ptr<Object> pPlayer);
	~RestoreHealth();

	void consumePotion(std::shared_ptr<Object> spPlayer);
};

class PoisonHealth : public Potion {
public:
	PoisonHealth(std::shared_ptr<Object> pPlayer);
	~PoisonHealth();

	void consumePotion(std::shared_ptr<Object> spPlayer);
};

class BoostAttack : public Potion {
public:
	BoostAttack(std::shared_ptr<Object> pPlayer);
	~BoostAttack();

	int consumePotion();
};

class WoundAttack : public Potion {
public:
	WoundAttack(std::shared_ptr<Object> pPlayer);
	~WoundAttack();

	int consumePotion();
};

class BoostDefense : public Potion {
public:
	BoostDefense(std::shared_ptr<Object> pPlayer);
	~BoostDefense();

	int consumePotion();
};

class WoundDefense : public Potion {
public:
	WoundDefense(std::shared_ptr<Object> pPlayer);
	~WoundDefense();

	int consumePotion();
};

#endif