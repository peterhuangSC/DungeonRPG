#ifndef __POTIONGENERATOR_H__
#define __POTIONGENERATOR_H__

#include <string>
#include <memory>

#include "potion.h"
#include "specificPotions.h"

class PotionGenerator {
public:
	std::shared_ptr<Potion> spawnPotion();
	std::shared_ptr<Potion> spawnPotion(int type);
};

#endif
