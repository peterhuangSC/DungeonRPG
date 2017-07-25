#ifndef __LADDERGENERATOR_H__
#define __LADDERGENERATOR_H__

#include <memory>
#include "ladder.h"

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

class LadderGenerator {
public:
	//spawns in the room YOU specify
	std::shared_ptr<Ladder> spawnLadder(int chamber);
	void reset();
};

#endif
