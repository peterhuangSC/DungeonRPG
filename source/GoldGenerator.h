#ifndef __GOLDGENERATOR_H__
#define __GOLDGENERATOR_H__

#include <memory>
#include <string>
#include "gold.h"
#include "EnemyGenerator.h"

/* Author, Coded & Developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class GoldGenerator {
public:
	std::shared_ptr<Gold> spawnGold();
	std::shared_ptr<Gold> spawnGold(char specificType);
	std::shared_ptr<Gold> spawnGold(int type);
	std::shared_ptr<Gold> spawnGold(int amount, int quantity);
	void reset();
};

#endif
