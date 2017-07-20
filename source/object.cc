#include <string>
#include "object.h"

Object::Object(char typeSymbol) : type{ typeSymbol } {
	//no implementation currently
}

Object::~Object() {}

void Object::setType(char newType) {
	this->type = newType;
}

char Object::getType() {
	return this->type;
}

void Object::notify(Object* who) {
	// to be implemented
}
