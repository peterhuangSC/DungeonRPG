#ifndef __SPECIFIC_POTIONS_H__
#define __SPECIFIC_POTIONS_H__

#include <string>
#include <vector>
#include <memory>
#include "potion.h"

class RestoreHealth : public Potion {
	static bool rhVisible;
public:
	RestoreHealth();
	~RestoreHealth();

	void setKnown() override;
};

class PoisonHealth : public Potion {
	static bool phVisible;
public:
	PoisonHealth();
	~PoisonHealth();

	void setKnown() override;
};

class BoostAttack : public Potion {
	static bool baVisible;
public:
	BoostAttack(std::shared_ptr<Potion> np);
	~BoostAttack();

	std::vector<int> potionBuffers() override;

	void setKnown() override;
};

class WoundAttack : public Potion {
	static bool waVisible;
public:
	WoundAttack(std::shared_ptr<Potion> np);
	~WoundAttack();

	std::vector<int> potionBuffers() override;

	void setKnown() override;
};

class BoostDefense : public Potion {
	static bool bdVisible;
public:
	BoostDefense(std::shared_ptr<Potion> np);
	~BoostDefense();

	std::vector<int> potionBuffers() override;

	void setKnown() override;
};

class WoundDefense : public Potion {
	static bool wdVisible;
public:
	WoundDefense(std::shared_ptr<Potion> np);
	~WoundDefense();

	std::vector<int> potionBuffers() override;

	void setKnown() override;
};

#endif
