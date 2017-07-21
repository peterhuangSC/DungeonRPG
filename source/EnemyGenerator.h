#ifndef __ENEMYGENERATOR_H__
#define __ENEMYGENERATOR_H__

#include <memory>
#include <string>
#include "enemy.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"

class EnemyGenerator {
public:
	std::shared_ptr<Enemy> spawnEnemy();
	std::shared_ptr<Enemy> spawnEnemy(char specificType);
};

#endif