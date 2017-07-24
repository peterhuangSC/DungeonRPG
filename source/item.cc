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
