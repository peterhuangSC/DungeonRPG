#ifndef __LADDER_H__
#define __LADDER_H__

#include <iostream>
#include "item.h"

class Player;

class Ladder : public Item {
protected:
	//char mapSymbol;
	int currentChamber;
public:
	Ladder();
	Ladder(int chamber);
	~Ladder();

	void consume(Player* player);
};

#endif