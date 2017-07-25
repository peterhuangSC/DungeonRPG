#include <map>
#include <vector>
#include <iostream>
#include "item.h"

using namespace std;

/* This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur) */

Item::Item(char itemType) : 
	Object(itemType), mapSymbol{ itemType } {}

Item::~Item() {}

char Item::getItemType() {
	return this->mapSymbol;
}
