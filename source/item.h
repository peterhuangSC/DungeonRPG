#ifndef __ITEM_H__
#define __ITEM_H__

#include <iostream>

class Character;

class Item {
protected:
	char mapSymbol;
public:
	Item();
	Item(char itemType);
	~Item();

	virtual void consume(Character* player) = 0;
	virtual char getItemType();
};

#endif