#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

class Object {
	//no private fields needed so far
protected:
	void setType(char newType);

public: 
	char type;

	Object(char typeSymbol);
	~Object();

	char getType();

	virtual void notify(Object* who);
};

#endif