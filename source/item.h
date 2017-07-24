#ifndef __ITEM_H__
#define __ITEM_H__

#include <iostream>
#include "object.h"

class Character;

class Item : public Object {
protected:
	char mapSymbol;
public:
	Item(char itemType);
	~Item();

	virtual char getItemType();
};

#endif
