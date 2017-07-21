#include <string>
#include "gold.h"

using namespace std;

/* Protected attributes
	int amount, int quantity, bool guarded;
*/


Gold::Gold(int gValue = 1, int gQuantity = 1, bool gGuarded = false) :
	Item('G'), amount{ gValue }, quantity{ gQuantity }, guarded{ gGuarded } {}

Gold::~Gold() {}

//this method return true if player is successful to pick up the gold
bool Gold::consumeGold(shared_ptr<Object> spPlayer) {
	//double check how gold picking up works when theres 2 piles ie human
	if (!guarded) {
		spPlayer->addGold(amount * quantity);
		return true;
	}
	return false;
}

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
	return this->guarded;
}

void Gold::setGuarded() {
	this->guarded = true;
}

void Gold::setUnguarded() {
	this->guarded = false;
}

