#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <memory>

class Object {
	//no private fields needed so far
protected:
	char type;
	void setType(char newType);
public: 
	Object(char typeSymbol);
	~Object();

	virtual char getType();

	virtual std::string getHeroType();

	virtual int getHealth();
	virtual void setHealth(int newHealth);
	virtual int getAttack();
	virtual int getDefense();

	virtual int getHealthEffect();
	virtual int getAttackEffect();
	virtual int getDefenseEffect();

	virtual void notify(Object* who);
	virtual int consumePotion();
	virtual void consumePotion(std::shared_ptr<Object> myObj);
};

#endif