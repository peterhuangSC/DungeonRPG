#include <string>
#include "gold.h"

using namespace std;

/* Protected attributes
	int amount, int quantity, bool guarded;
*/


Gold::Gold(int gValue = 1, int gQuantity = 1, bool gGuarded = false) :
	Item('G'), amount{ gValue }, quantity{ gQuantity }, guarded{ gGuarded } {}

Gold::~Gold() {}

void Gold::consume(Character* player) {}

char Gold::getItemType() {
	return this->mapSymbol;
}

int Gold::getValue() {
	return this->amount;
}
void Gold::setValue(int newValue) {
	this->amount = newValue;
}

int Gold::getQuantity() {
	return this->quantity;
}

void Gold::setQuantity(int newQty) {
	this->quantity = newQty;
}

bool Gold::isGuarded() {
	return this->isGuarded;
}

void Gold::setGuarded() {
	this->isGuarded = true;
}

void Gold::setUnguarded() {
	this->isGuarded = false;
}

