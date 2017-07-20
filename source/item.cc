#include <map>
#include <vector>
#include <iostream>
#include "item.h"

using namespace std;

Item::Item(char itemType) : 
	Object(itemType), mapSymbol{ itemType } {}

Item::~Item() {}

char Item::getItemType() {
	return this->mapSymbol;
}

/*
void Item::consume(Character* player) {
	//attach this potion to the player

	//override it in health potions so it doesn't attach
}
*/

//remove item from grid?