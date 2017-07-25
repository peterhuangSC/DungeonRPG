#include <string>
#include "gold.h"

using namespace std;


/* 
This project was coded & developed by Peter Huang (zh3huang) and Shane Mazur (smazur)
Protected attributes
  int amount, int quantity, bool guarded;
*/


Gold::Gold(int gValue, int gQuantity, bool gGuarded) : Item('G'), 
	amount{ gValue }, quantity{ gQuantity }, guarded{ gGuarded } {}

Gold::~Gold() {}

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

void Gold::notify(shared_ptr<Object> player) {
	if (!isGuarded()) {
		player->appendAction(" PC sees treasure.");
	}
	else {
		player->appendAction(" PC sees a guarded dragon hoard.");
	}
}

