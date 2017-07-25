#include "LadderGenerator.h"

using namespace std;

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

shared_ptr<Ladder> LadderGenerator::spawnLadder(int chamber) {
	return make_shared<Ladder>(chamber);
	//maybe more complex generations in the future but for
	//now this is the standard ladder
}

void LadderGenerator::reset() {}
