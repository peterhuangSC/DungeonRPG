#ifndef __PLAYERGENERATOR_H__
#define __PLAYERGENERATOR_H__

/* Author, Coded & Developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

#include <string>
#include <memory>
#include "player.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"

class PlayerGenerator {
public:
	std::shared_ptr<Player> spawnPlayer(char type);
	void reset();
};

#endif
