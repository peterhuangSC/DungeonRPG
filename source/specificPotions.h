#ifndef __SPECIFIC_POTIONS_H__
#define __SPECIFIC_POTIONS_H__

#include <string>
#include <vector>
#include <memory>
#include "potion.h"

class RestoreHealth : public Potion {
public:
	RestoreHealth();
	~RestoreHealth();
};

class PoisonHealth : public Potion {
public:
	PoisonHealth();
	~PoisonHealth();
};

class BoostAttack : public Potion {
public:
	BoostAttack(std::shared_ptr<Potion> np);
	~BoostAttack();

	std::vector<int> potionBuffers() override;
};

class WoundAttack : public Potion {
public:
	WoundAttack(std::shared_ptr<Potion> np);
	~WoundAttack();

	std::vector<int> potionBuffers() override;
};

class BoostDefense : public Potion {
public:
	BoostDefense(std::shared_ptr<Potion> np);
	~BoostDefense();

	std::vector<int> potionBuffers() override;
};

class WoundDefense : public Potion {
public:
	WoundDefense(std::shared_ptr<Potion> np);
	~WoundDefense();

	std::vector<int> potionBuffers() override;
};

#endif