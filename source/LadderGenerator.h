#ifndef __LADDERGENERATOR_H__
#define __LADDERGENERATOR_H__

#include <memory>
#include "ladder.h"

class LadderGenerator {
public:
	//spawns in the room YOU specify
	std::shared_ptr<Ladder> spawnLadder(int chamber);
};

#endif
